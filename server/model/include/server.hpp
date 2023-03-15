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

public:
    GameSession(Player first_player, Player second_player)
        : first_player(first_player), second_player(second_player) {
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
        const namespace_proto::User *request,
        ::grpc::ServerWriter<::namespace_proto::GameState> *response
    ) override {
        get_server_state()->wait_list.push(Player{request->id(), response});
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
            &(get_server_state()->game_sessions[request->game_id()]);
        namespace_proto::GameState *game_state_ref =
            game_session_ref->get_game_state();
        namespace_proto::Unit *unit =
            game_state_ref
                ->mutable_game_cells(
                    request->start().y() * 10 + request->start().x()
                )
                ->mutable_unit();
        game_state_ref
            ->mutable_game_cells(
                request->finish().y() * 10 + request->finish().x()
            )
            ->set_allocated_unit(unit);
        game_state_ref
            ->mutable_game_cells(
                request->start().y() * 10 + request->start().x()
            )
            ->set_allocated_unit(nullptr);
        if (request->user_id() !=
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
};

void RunServer(const std::string &address, ServerServices *services);
