#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include <atomic>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <random>
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

class ServerServices final : public ::namespace_proto::Server::Service {
    ::grpc::Status SignUp(
        ::grpc::ServerContext *context,
        const namespace_proto::LogInData *request,
        namespace_proto::User *response
    ) override {
        int id = rand();
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
        int id = rand();
        std::unique_lock lock{get_server_state()->db_mutex};
        get_server_state()->data_base.get_user(request->name());
        if (callback_data.password == request->password()) {
            response->set_id(id);
            response->set_rate(callback_data.rating);
            response->set_name(request->name());
        } else {
            response->set_id(-1);
        }
        return grpc::Status::OK;
    }

    ::grpc::Status CallServer(
        ::grpc::ServerContext *context,
        const namespace_proto::UserState *request,
        ::grpc::ServerWriter<::namespace_proto::GameState> *response
    ) override {
        get_server_state()->wait_list.push(Player{
            request->user().id(), response});
        while (true) {
        }
        return ::grpc::Status::OK;
    }

    static void
    swapUnits(namespace_proto::Cell *cell1, namespace_proto::Cell *cell2) {
        cell1->Swap(cell2);
        int temp_row = cell1->row();
        int temp_column = cell1->column();
        int temp_strength = cell1->durability();
        cell1->set_durability(cell2->durability());
        cell2->set_durability(temp_strength);
        cell1->set_row(cell2->row());
        cell1->set_column(cell2->column());
        cell2->set_row(temp_row);
        cell2->set_column(temp_column);
    }

    static void update_unit(
        namespace_proto::Unit *unit,
        const game_model::coordinates &coordinates,
        GameSession *game_session_res
    ) {
        game_model::game *model_game = game_session_res->get_model_game();
        game_model::cell cell = model_game->get_cell(coordinates);
        game_model::unit model_unit =
            model_game->get_player(cell.get_player_index())
                ->get_unit(cell.get_unit_index());
        unit->set_sum_of_health(model_unit.get_health());
        unit->set_amount_unit(model_unit.get_number());
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
        namespace_proto::Cell *cell_from = game_state_ref->mutable_game_cells(
            request->start().row() * 10 + request->start().column()
        );
        game_model::coordinates to(request->finish());
        namespace_proto::Cell *cell_to = game_state_ref->mutable_game_cells(
            request->finish().row() * 10 + request->finish().column()
        );
        if (game_session_ref->get_model_game()->get_cell(to).get_unit_index() ==
            -1) {
            (*game_session_ref->get_mover())(from, to);
            swapUnits(cell_from, cell_to);
        } else {
            std::cout << "attack selected\n";
            (*game_session_ref->get_attacker())(from, to);
            if (game_session_ref->get_model_game()->get_cell(to).get_unit_index(
                ) == -1) {
                // delete to;
                std::cout << "delete to\n";
                //cell_to->set_allocated_unit(nullptr);
                cell_to->set_is_unit(false);
            } else {
                update_unit(cell_to->mutable_unit(), to, game_session_ref);
            }
            if (game_session_ref->get_model_game()->get_cell(from).get_unit_index(
                ) == -1) {
                //cell_from->set_allocated_unit(nullptr);
                cell_from->set_is_unit(false);
                std::cout << "delete from\n";
                // delete from;
            } else {
                update_unit(cell_from->mutable_unit(), from, game_session_ref);
            }
        }

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
        auto enable_cells = (*game_session_ref->get_move_selecter()
        )(selected, request->user().user().id());
        std::cout << enable_cells.size() << '\n';
        for (auto cell : enable_cells) {
            namespace_proto::Cell *new_cell = response->add_cells();
            new_cell->set_row(cell.get().get_coordinates().get_row());
            new_cell->set_column(cell.get().get_coordinates().get_column());
        }
        enable_cells = (*game_session_ref->get_attack_selecter()
        )(selected, request->user().user().id());
        for (auto cell : enable_cells) {
            namespace_proto::Cell *new_cell = response->add_cells();
            new_cell->set_row(cell.get().get_coordinates().get_row());
            new_cell->set_column(cell.get().get_coordinates().get_column());
            new_cell->set_is_attack(true);
        }
        std::cout << enable_cells.size() << '\n';
        return ::grpc::Status::OK;
    }
};

void RunServer(const std::string &address, ServerServices *services);

#endif  // SERVER_HPP_
