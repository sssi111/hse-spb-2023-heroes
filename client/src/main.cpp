#include <SFML/Graphics.hpp>
#include <future>
#include <iostream>
#include "client.hpp"
#include "game.hpp"

enum class request_type { SendOk, ReceiveGameBoard, AddToLobby };

struct Request {
    request_type type;
    grpc::ClientContext context;
};

void run_request(Client *client, const Request &request) {
    //    if (request.type == request_type::SendOk) {
    //        client->getStub()->SendOk();
    //    } else if (request.type == request_type::ReceiveGameBoard) {
    //        client->getStub()->AsyncReceiveGameBoard();
    //    } else if (request.type == request_type::AddToLobby){
    //        client->getStub()->AddToLobby();
    //    }
}

int main(int argc, char *argv[]) {
    auto channel = grpc::CreateChannel(
        "localhost:55555", grpc::InsecureChannelCredentials()
    );
    Request request;
    std::unique_ptr<Client> client = std::make_unique<Client>(channel);
    std::async(
        std::launch::async, run_request, client.get(), std::cref(request)
    );

    Game game;
    while (!game.get_window()->is_done()) {
        game.update();
        game.render();
    }

    return 0;
}