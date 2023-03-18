#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include <atomic>
#include <game_session.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include "TSqueue.hpp"
#include "choose_interactor.hpp"
#include "game.hpp"
#include "move_interactor.hpp"
#include "proto/all_protos/demo.grpc.pb.h"

class Player final {
    int id;
    ::grpc::ServerWriter<namespace_proto::GameState> *stream;

public:
    Player(int id, ::grpc::ServerWriter<namespace_proto::GameState> *stream)
        : id(id), stream(stream) {
    }

    [[nodiscard]] int get_id() const {
        return id;
    }

    [[nodiscard]] ::grpc::ServerWriter<namespace_proto::GameState> *get_stream(
    ) const {
        return stream;
    }
};

class GameSession {
    Player first_player;
    Player second_player;
    std::unordered_map<int, TSQueue<namespace_proto::GameState>>
        response_queues;
    namespace_proto::GameState game_state;
    game_model::game model_game;
    interactors::mover move_unit;
    interactors::chooser choose_unit;

public:
    GameSession(Player first_player_, Player second_player_)
        : first_player(first_player_),
          second_player(second_player_),
          model_game(first_player_.get_id(), second_player_.get_id()),
          move_unit(model_game),
          choose_unit(model_game) {
    }

    Player get_first_player() const {
        return first_player;
    }

    Player get_second_player() const {
        return second_player;
    }

    std::unordered_map<int, TSQueue<namespace_proto::GameState>>
        *get_response_queues() {
        return &response_queues;
    }

    namespace_proto::GameState *get_game_state() {
        return &game_state;
    }

    game_model::game *get_model_game() {
        return &model_game;
    }

    interactors::mover *get_mover() {
        return &move_unit;
    }

    interactors::chooser *get_chooser() {
        return &choose_unit;
    }
};

class ServerState {
public:
    std::vector<GameSession> game_sessions;
    TSQueue<Player> wait_list;
    mutable std::mutex server_mutex;
};

ServerState *get_server_state();

// todo include all interactors

class ServerServices final : public ::namespace_proto::Server::Service {
    ::grpc::Status CallServer(
        ::grpc::ServerContext *context,
        const namespace_proto::UserState *request,
        ::grpc::ServerWriter<::namespace_proto::GameState> *response
    ) override {
        get_server_state()->wait_list.push(Player{request->user_id(), response}
        );
        std::cout << get_server_state()->wait_list.size();
        while (true) {
        }
        return ::grpc::Status::OK;
    }

    ::grpc::Status MoveUnit(
        ::grpc::ServerContext *context,
        const ::namespace_proto::MoveFromTo *request,
        ::namespace_proto::GameState *response
    ) override {
        GameSession *game_session_ref =
            &(get_server_state()->game_sessions[request->user().game_id()]);
        namespace_proto::GameState *game_state_ref =
            game_session_ref->get_game_state();
        game_model::coordinates from(request->start());
        game_model::coordinates to(request->finish());
        (*game_session_ref->get_mover())(from, to);
        namespace_proto::Unit *unit =
            game_state_ref
                ->mutable_game_cells(
                    request->start().row() * 10 + request->start().column()
                )
                ->mutable_unit();
        game_state_ref
            ->mutable_game_cells(
                request->finish().row() * 10 + request->finish().column()
            )
            ->set_allocated_unit(unit);
        game_state_ref
            ->mutable_game_cells(
                request->start().row() * 10 + request->start().column()
            )
            ->set_allocated_unit(nullptr);
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
        response = game_state_ref;
        return ::grpc::Status::OK;
    }

    ::grpc::Status SelectUnit(
        ::grpc::ServerContext *context,
        const ::namespace_proto::MoveSelectUnit *request,
        ::namespace_proto::EnableCell *response
    ) override {
        GameSession *game_session_ref =
            &(get_server_state()->game_sessions[request->user().game_id()]);
        namespace_proto::GameState *game_state_ref =
            game_session_ref->get_game_state();
        // вызывает интерактор
        //        for (int i = 0; i < 100; ++i) {
        //            namespace_proto::Cell *new_cell =
        //            game_state_ref->add_game_cells();
        //            new_cell->set_allocated_unit(nullptr);
        //            new_cell->set_id_hero(-1);
        //            new_cell->set_x(i % 10);
        //            new_cell->set_y(i / 10);
        //        }
        return ::grpc::Status::OK;
    }
};

void RunServer(const std::string &address, ServerServices *services);
