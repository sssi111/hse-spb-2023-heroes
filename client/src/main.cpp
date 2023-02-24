#include <all_protos/demo.grpc.pb.h>
#include <all_protos/demo_client.pb.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <SFML/Graphics.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
    auto local_channel = grpc::CreateChannel(
        "localhost:50051", grpc::InsecureChannelCredentials()
    );

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
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
