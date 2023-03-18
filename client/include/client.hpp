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
    std::unique_ptr<namespace_proto::Server::Stub> m_stub = nullptr;
    namespace_proto::UserState m_user;
    namespace_proto::GameState m_game_state;
    mutable std::mutex m_mutex;
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
    static void move_unit(namespace_proto::Cell from, namespace_proto::Cell to);
};

#endif  // CLIENT_HPP_
