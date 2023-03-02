#include <all_protos/demo.grpc.pb.h>
#include <all_protos/demo_client.pb.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.hpp"

int main(int argc, char *argv[]) {
    auto local_channel = grpc::CreateChannel(
        "localhost:50051", grpc::InsecureChannelCredentials()
    );

    Game game;
    while (!game.get_window()->is_done()) {
        game.handle_input();
        game.update();
        game.render();
    }

    ::demo_name::GetOk request;
    ::demo_name::Ok response;

    response.set_ok(false);

    std::unique_ptr<demo_name::ClientToServer::Stub> stub =
        demo_name::ClientToServer::NewStub(local_channel);
    grpc::ClientContext context;
    grpc::Status status = stub->SendOk(&context, request, &response);

    std::cout << "server response " << response.ok() << std::endl;

    return 0;
}