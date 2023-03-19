#include "client.hpp"
#include <utility>
#include "game.hpp"

[[nodiscard]] ClientState *get_client_state() {
    static ClientState clientState;
    return &clientState;
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
            get_game_state()->get_board()->update_board(
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
    request.set_allocated_start(&from);
    request.set_allocated_finish(&to);
    request.set_allocated_user(&(get_client_state()->m_user));
    get_client_state()->m_stub->MoveUnit(
        &context, request, &(get_client_state()->m_game_state)
    );
}

std::vector<std::pair<int, int>> Client::select_unit(
    namespace_proto::Cell selected
) {
    grpc::ClientContext context;
    namespace_proto::MoveSelectUnit request;
    namespace_proto::Cell *request_cell = new namespace_proto::Cell;
    *request_cell = std::move(selected);
    request.set_allocated_unit(request_cell);
    namespace_proto::UserState *request_user = new namespace_proto::UserState;
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