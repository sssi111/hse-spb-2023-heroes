#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include <atomic>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include "TSqueue.hpp"
#include "proto/all_protos/demo.grpc.pb.h"

class ServerState {
public:
    int last_game_id = 0;
    std::vector<namespace_proto::GameState> games;
    std::vector<std::vector<TSQueue<bool>>> call_queues;
    TSQueue<namespace_proto::User> wait_list;
};

ServerState *get_server_state();

// todo include all interactors

class ServerServices final : public ::namespace_proto::Server::Service {
    ::grpc::Status CallServer(
        ::grpc::ServerContext *context,
        const namespace_proto::GameIdAndHero *request,
        ::grpc::ServerWriter<::namespace_proto::GameState> *response
    ) override {
        std::thread([&request, &response]() mutable {
            while (true) {
                if (!get_server_state()
                         ->call_queues[request->game_id()]
                                      [request->position_in_call_queue()]
                         .empty()) {
                    response->Write(
                        get_server_state()->games[request->game_id()]
                    );
                }
            }
        }).detach();
        return ::grpc::Status::OK;
    }

    ::grpc::Status ReceiveGameState(
        ::grpc::ServerContext *context,
        const ::namespace_proto::GameId *request,
        ::namespace_proto::GameState *response
    ) override {
        *response = get_server_state()->games[request->game_id()];
        return ::grpc::Status::OK;
    }

    ::grpc::Status AddToLobby(
        ::grpc::ServerContext *context,
        const namespace_proto::User *request,
        ::namespace_proto::GameId *response
    ) override {
        get_server_state()->wait_list.push(*request);
        std::thread([&request, &response]() mutable {
            while (true) {
                if (get_server_state()->wait_list.front().id() !=
                        request->id() &&
                    get_server_state()->wait_list.size() > 2) {
                    break;
                }
            }
        }).detach();
        return ::grpc::Status::OK;
    }

    ::grpc::Status MoveUnit(
        ::grpc::ServerContext *context,
        const ::namespace_proto::MoveFromTo *request,
        ::namespace_proto::GameBoard *response
    ) override {
        return ::grpc::Status::OK;
    }
};

class Server {
private:
    ServerServices *service;
    std::unique_ptr<grpc::ServerCompletionQueue> server_queue;
    std::unique_ptr<grpc::Server> server;
    std::string address;
    std::vector<std::thread> games_threads;

public:
    Server(std::string address, ServerServices *services, int number_of_threads)
        : address(std::move(address)) {
        service = services;
        games_threads.resize(number_of_threads);
    }

    std::thread start();
    void stop();
};