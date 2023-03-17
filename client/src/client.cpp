#include "client.hpp"
#include "game.hpp"

ClientState *get_client_state() {
    static ClientState clientState;
    return &clientState;
}

void Client::run_receiver() {
    namespace_proto::GameState response;
    grpc::ClientContext context{};
    std::unique_ptr<grpc::ClientReader<namespace_proto::GameState> > reader(
        get_client_state()->stub_->CallServer(
            &context, get_client_state()->user_
        )
    );
    while (reader->Read(&response)) {
        {
            std::unique_lock lock{get_client_state()->mutex_};
            get_client_state()->game_state_ = response;
            get_game_state()->get_board()->update_board(get_client_state()->game_state_);
        }
        std::cout << get_client_state()->game_state_.game_id() << '\n';
    }
}