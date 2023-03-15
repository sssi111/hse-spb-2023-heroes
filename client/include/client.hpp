#ifndef CLIENT_HPP_
#define CLIENT_HPP_
#include <all_protos/demo.grpc.pb.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <memory>
#include <mutex>
#include <thread>

class ClientState final {
public:
    std::unique_ptr<namespace_proto::Server::Stub> stub_ = nullptr;
    namespace_proto::User user_;
    namespace_proto::GameState game_state_;
    std::mutex mutex_;
};

ClientState *get_client_state();

class Client final {
public:
    Client(const Client &) = delete;
    Client &operator=(const Client &) = delete;
    Client(Client &&) = delete;
    Client &operator=(Client &&) = delete;

public:
    static void run_receiver();
};

#endif  // CLIENT_HPP_
