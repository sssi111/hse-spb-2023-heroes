#include <all_protos/demo.grpc.pb.h>
#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include <atomic>
#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <utility>
#include <vector>

class ServerState {
public:
    std::vector<namespace_proto::GameBoard> games;
    std::deque<namespace_proto::User> wait_list;
};

ServerState *get_server_state();

// todo include all interactors

class ServerServices final : public ::namespace_proto::Server::AsyncService {
    ::grpc::Status SendOk(
        ::grpc::ServerContext *context,
        const ::namespace_proto::GetOk *request,
        ::namespace_proto::Ok *response
    ) override {
        std::cout << "server woke up" << std::endl;
        response->set_ok(true);
        return ::grpc::Status::OK;
    }

    ::grpc::Status CallClient(
        ::grpc::ServerContext *context,
        const ::google::protobuf::Empty *request,
        ::grpc::ServerWriter<::namespace_proto::CallMe> *response
    ) override {
        // response->;
        return ::grpc::Status::OK;
    }

    ::grpc::Status ReceiveGameBoard(
        ::grpc::ServerContext *context,
        const ::namespace_proto::GameId *request,
        ::namespace_proto::GameBoard *response
    ) override {
        *response = get_server_state()->games[request->game_id()];
        return ::grpc::Status::OK;
    }

    ::grpc::Status AddToLobby(
        ::grpc::ServerContext *context,
        const ::namespace_proto::User *request,
        ::namespace_proto::GameId *response
    ) override {
        get_server_state()->wait_list.push_back(*request);
        return ::grpc::Status::OK;
    }

    ::grpc::Status MoveFromTo(
        ::grpc::ServerContext *context,
        const ::namespace_proto::FromTo *request,
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

    std::vector<std::thread> game_threads;

public:
    Server(std::string address, ServerServices *services, int number_of_threads)
        : address(std::move(address)) {
        service = services;
        game_threads.resize(number_of_threads);
    }

    std::thread start();
    void stop();
};