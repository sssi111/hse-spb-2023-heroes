#include <future>
#include "client.hpp"
#include "game.hpp"

int main() {
    const std::shared_ptr< ::grpc::ChannelInterface> &channel =
        grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials()
        );
    get_client_state()->stub_ =
        std::make_unique<namespace_proto::Server::Stub>(channel);
    namespace_proto::UserState user;
    user.set_user_id(2);
    get_client_state()->user_ = user;
    std::thread receiver(&Client::run_receiver);
    while (!get_game_state()->get_window()->is_done()) {
        {
            std::unique_lock lock{get_client_state()->mutex_};
            get_game_state()->update();
        }
        get_game_state()->render();
    }
    receiver.join();
    return 0;
}