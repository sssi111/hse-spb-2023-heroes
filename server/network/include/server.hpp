#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include <atomic>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include "db_interface.hpp"
#include "game_session.hpp"

class ServerState {
public:
    db data_base;
    std::vector<GameSession> game_sessions;
    TSQueue<Player> wait_list;
    mutable std::mutex server_mutex;
    mutable std::mutex db_mutex;
};

ServerState *get_server_state();

int get_db_size();

class ServerServices final : public ::namespace_proto::Server::Service {

    ::grpc::Status SignUp(
        ::grpc::ServerContext *context,
        const namespace_proto::LogInData *request,
        namespace_proto::User *response
    ) override {
        int id = get_db_size();
        get_server_state()->data_base.insert(
            request->name().c_str(), request->password().c_str(), 1000
        );
        response->set_id(id);
        response->set_rate(1000);
        response->set_name(request->name());
        return grpc::Status::OK;
    }

    ::grpc::Status LogIn(
        ::grpc::ServerContext *context,
        const namespace_proto::LogInData *request,
        namespace_proto::User *response
    ) override {
        int id = get_db_size();
        std::unique_lock lock{get_server_state()->db_mutex};
        get_server_state()->data_base.get_user(
            request->name()
        );
        if (callback_data.password == request->password()){
            response->set_id(id);
            response->set_rate(callback_data.rating);
            response->set_name(request->name());
        }
        return grpc::Status::OK;
    }

    ::grpc::Status CallServer(
        ::grpc::ServerContext *context,
        const namespace_proto::UserState *request,
        ::grpc::ServerWriter<::namespace_proto::GameState> *response
    ) override {
        get_server_state()->wait_list.push(Player{request->user().id(), response}
        );
        while (true) {
        }
        return ::grpc::Status::OK;
    }

    static void swapUnits(namespace_proto::Cell *cell1, namespace_proto::Cell *cell2) {
        cell1->Swap(cell2);
        int temp_row = cell1->row();
        int temp_column = cell1->column();
        int temp_strength = cell1->strength();
        cell1->set_strength(cell2->strength());
        cell2->set_strength(temp_strength);
        cell1->set_row(cell2->row());
        cell1->set_column(cell2->column());
        cell2->set_row(temp_row);
        cell2->set_column(temp_column);
    }

    ::grpc::Status MoveUnit(
        ::grpc::ServerContext *context,
        const ::namespace_proto::MoveFromTo *request,
        ::namespace_proto::GameState *response
    ) override {
        std::cout << request->start().row() << ' ' << request->start().column()
                  << '\n';
        std::cout << request->finish().row() << ' '
                  << request->finish().column() << '\n';
        GameSession *game_session_ref =
            &(get_server_state()->game_sessions[request->user().game_id()]);
        namespace_proto::GameState *game_state_ref =
            game_session_ref->get_game_state();
        game_model::coordinates from(request->start());
        game_model::coordinates to(request->finish());
        (*game_session_ref->get_mover())(from, to);
        swapUnits(
            game_state_ref->mutable_game_cells(
                request->start().row() * 10 + request->start().column()
            ),
            game_state_ref->mutable_game_cells(
                request->finish().row() * 10 + request->finish().column()
            )
        );
        if (request->user().user().id() !=
            game_session_ref->get_first_player().get_id()) {
            (*(game_session_ref->get_response_queues())
            )[game_session_ref->get_first_player().get_id()]
                .push(*game_state_ref);
        } else {
            (*(game_session_ref->get_response_queues())
            )[game_session_ref->get_second_player().get_id()]
                .push(*game_state_ref);
        }
        *response = *game_state_ref;
        return ::grpc::Status::OK;
    }

    ::grpc::Status SelectUnit(
        ::grpc::ServerContext *context,
        const ::namespace_proto::MoveSelectUnit *request,
        ::namespace_proto::EnableCell *response
    ) override {
        GameSession *game_session_ref =
            &(get_server_state()->game_sessions[request->user().game_id()]);
        game_model::coordinates selected(request->unit());
        auto enable_cells = (*game_session_ref->get_chooser()
        )(selected, request->user().user().id());
        std::cout << enable_cells.size() << '\n';
        for (auto cell : enable_cells) {
            namespace_proto::Cell *new_cell = response->add_cells();
            new_cell->set_row(cell.get().get_coordinates().get_row());
            new_cell->set_column(cell.get().get_coordinates().get_column());
        }
        return ::grpc::Status::OK;
    }
};

void RunServer(const std::string &address, ServerServices *services);

#endif // SERVER_HPP_
