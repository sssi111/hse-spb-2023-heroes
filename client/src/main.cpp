#include <all_protos/demo.pb.h>

#include <SFML/Graphics.hpp>
#include <grpcpp/create_channel.h>
#include <iostream>
#include <grpcpp/client_context.h>


int main(int argc, char* argv[])
{

    auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }



    return 0;
}
