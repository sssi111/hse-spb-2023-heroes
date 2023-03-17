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
            get_game_state()->get_board()->update_board(
                get_client_state()->game_state_
            );
        }
        get_client_state()->user_.set_game_id(
            get_client_state()->game_state_.game_id()
        );
        std::cout << get_client_state()->game_state_.game_id() << '\n';
    }
}

void Client::move_unit(namespace_proto::Cell from, namespace_proto::Cell to) {
    grpc::ClientContext *context{};
    namespace_proto::MoveFromTo request;
    request.set_allocated_start(&from);
    request.set_allocated_finish(&to);
    request.set_allocated_user(&(get_client_state()->user_));
    get_client_state()->stub_->MoveUnit(
        context, request, &(get_client_state()->game_state_)
    );
}