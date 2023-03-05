#include <SFML/Graphics.hpp>
#include <future>
#include <iostream>
#include "client.hpp"
#include "game.hpp"

// enum class request_type { SendOk, ReceiveGameBoard, AddToLobby };
//
// struct Request {
//     request_type type;
//     grpc::ClientContext context;
// };
//
// void run_request(Client *client, const Request &request) {
//             if (request.type == request_type::SendOk) {
//                 client->getStub()->SendOk();
//             }
//             else if (request.type == request_type::ReceiveGameBoard) {
//                 client->getStub()->AsyncReceiveGameBoard();
//             } else if (request.type == request_type::AddToLobby){
//                 client->getStub()->AddToLobby();
//             }
//             grpc::ServerContext *context;
//      client->getStub()->CallClient(context, Ser );
// }

int main(int argc, char *argv[]) {
    auto channel = grpc::CreateChannel(
        "localhost:55555", grpc::InsecureChannelCredentials()
    );

    std::unique_ptr<Client> client = std::make_unique<Client>(channel);
    grpc::ClientContext context{};
    namespace_proto::GameState game_state;
    namespace_proto::GameIdAndHero game_id_and_hero;
    std::mutex mutex;
    std::thread([&client, &context, &mutex, &game_state, &game_id_and_hero]() {
        namespace_proto::GameState response;
        std::unique_ptr<grpc::ClientReader<namespace_proto::GameState> > reader(
            client->getStub()->CallServer(&context, game_id_and_hero)
        );
        while (reader->Read(&response)) {
            std::unique_lock l{mutex};
            game_state = response;
        }
    }).detach();

    Game game;
    while (!game.get_window()->is_done()) {
        game.update();
        game.render();
    }

    return 0;
}