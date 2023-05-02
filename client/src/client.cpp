#include "client.hpp"
#include <utility>
#include "game.hpp"

[[nodiscard]] ClientState *get_client_state() {
    static ClientState clientState;
    return &clientState;
}

void Client::log_in(std::string nickname, std::string password) {
    namespace_proto::LogInData request;
    request.set_name(nickname);
    request.set_password(password);
    grpc::ClientContext context{};
    get_client_state()->m_stub->LogIn(
        &context, request, get_client_state()->m_user.mutable_user()
    );
}

void Client::sign_up(std::string nickname, std::string password) {
    namespace_proto::LogInData request;
    request.set_name(nickname);
    request.set_password(password);
    grpc::ClientContext context{};
    get_client_state()->m_stub->SignUp(
        &context, request, get_client_state()->m_user.mutable_user()
    );
    if (get_client_state()->m_user.user().id() == -1){
        std::cout << "try again\n";
    }
}

void Client::run_receiver() {
    namespace_proto::GameState response;
    grpc::ClientContext context{};
    std::unique_ptr<grpc::ClientReader<namespace_proto::GameState>> reader(
        get_client_state()->m_stub->CallServer(
            &context, get_client_state()->m_user
        )
    );
    while (reader->Read(&response)) {
        {
            std::unique_lock lock{get_client_state()->m_mutex};
            get_client_state()->m_game_state = response;
            game_view::get_game_state()->get_board()->update_board(
                get_client_state()->m_game_state
            );
        }
        get_client_state()->m_user.set_game_id(
            get_client_state()->m_game_state.game_id()
        );
        std::cout << get_client_state()->m_game_state.game_id() << '\n';
    }
}

void Client::move_unit(namespace_proto::Cell from, namespace_proto::Cell to) {
    grpc::ClientContext context;
    namespace_proto::MoveFromTo request;
    auto *request_from = new namespace_proto::Cell;
    auto *request_to = new namespace_proto::Cell;
    *request_from = from;
    *request_to = to;
    auto *request_user = new namespace_proto::UserState;
    *request_user = (get_client_state()->m_user);
    request.set_allocated_start(request_from);
    request.set_allocated_finish(request_to);
    request.set_allocated_user(request_user);
    namespace_proto::GameState response;
    get_client_state()->m_stub->MoveUnit(&context, request, &response);
    get_client_state()->m_game_state = response;
}

std::vector<std::pair<int, int>> Client::select_unit(
    namespace_proto::Cell selected
) {
    grpc::ClientContext context;
    namespace_proto::MoveSelectUnit request;
    auto *request_cell = new namespace_proto::Cell;
    *request_cell = selected;
    request.set_allocated_unit(request_cell);
    auto *request_user = new namespace_proto::UserState;
    *request_user = (get_client_state()->m_user);
    request.set_allocated_user(request_user);
    namespace_proto::EnableCell response;
    get_client_state()->m_stub->SelectUnit(&context, request, &response);
    std::vector<std::pair<int, int>> enable_set;
    for (const auto &cell : response.cells()) {
        enable_set.emplace_back(cell.row(), cell.column());
    }
    return enable_set;
}