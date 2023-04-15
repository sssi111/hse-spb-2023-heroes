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
#include "game_session.hpp"

class ServerState {
public:
    std::vector<GameSession> game_sessions;
    TSQueue<Player> wait_list;
    mutable std::mutex server_mutex;
};

ServerState *get_server_state();

class ServerServices final : public ::namespace_proto::Server::Service {
    ::grpc::Status CallServer(
        ::grpc::ServerContext *context,
        const namespace_proto::UserState *request,
        ::grpc::ServerWriter<::namespace_proto::GameState> *response
    ) override {
        get_server_state()->wait_list.push(Player{request->user_id(), response}
        );
        while (true) {
        }
        return ::grpc::Status::OK;
    }

    void swapUnits(namespace_proto::Cell *cell1, namespace_proto::Cell *cell2) {
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
        if (request->user().user_id() !=
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
        )(selected, request->user().user_id());
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
