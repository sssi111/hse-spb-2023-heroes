#include "server.hpp"

ServerState *get_server_state() {
    static ServerState server_state;
    return &server_state;
}

std::thread Server::start() {
    grpc::ServerBuilder builder;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(service);
    server_queue = builder.AddCompletionQueue();
    server = builder.BuildAndStart();

    while (true) {
        while (get_server_state()->wait_list.size() >= 2) {
            namespace_proto::User first_user =
                get_server_state()->wait_list.front();
            get_server_state()->wait_list.pop_front();
            namespace_proto::User second_user =
                get_server_state()->wait_list.front();
            get_server_state()->wait_list.pop_front();
            std::thread t([&first_user, &second_user]() {
                // todo game logic
            });
            game_threads.push_back(std::move(t));
        }
    }
}

void Server::stop() {
    server->Shutdown();
    server_queue->Shutdown();

    for (auto &worker : game_threads) {
        worker.join();
    }
}