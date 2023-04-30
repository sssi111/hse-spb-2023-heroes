#include "event_manager.hpp"
#include <iostream>
#include "client.hpp"

namespace game_view {
void EventManager::update_cell(
    CellEventType event_type,
    Unit **selected_unit,
    Unit **unit,
    Coords clicked_position,
    Board *board
) {
    if (event_type == CellEventType::FirstPress) {
        std::cout << "FirstPress is caught!\n";
        namespace_proto::Cell selected_cell;
        selected_cell.set_row(clicked_position.get_row());
        selected_cell.set_column(clicked_position.get_column());
        bool is_second =
            (get_client_state()->m_game_state.second_user() ==
             get_client_state()->m_user.user().id());
        if (is_second) {
            selected_cell = reverse_cell(selected_cell);
        }
        board->add_available_for_moving_cells(Client::select_unit(selected_cell)
        );
        std::cout << '\n' << "received\n";
        // selected_unit_id = unit_id;
        // board[row][column].set_selection(selected_unit_id);
        if (*selected_unit != nullptr) {
            (*selected_unit)->disable_selection();
        }
        *selected_unit = *unit;
        (*unit)->set_selection();
    } else if (event_type == CellEventType::SecondPress) {
        std::cout << "SecondPress is caught!\n";
        // send to server position of our unit to deactivate unit (?)
        board->remove_available_for_moving_cells();

        *selected_unit = nullptr;
        (*unit)->disable_selection();
    } else if (event_type == CellEventType::Move) {
        std::cout << "You wanna move?\n";
        namespace_proto::Cell to;
        to.set_row(clicked_position.get_row());
        to.set_column(clicked_position.get_column());
        namespace_proto::Cell from;
        from.set_row((*selected_unit)->get_coords().get_row());
        from.set_column((*selected_unit)->get_coords().get_column());
        bool is_second =
            (get_client_state()->m_game_state.second_user() ==
             get_client_state()->m_user.user().id());
        if (is_second) {
            from = reverse_cell(from);
            to = reverse_cell(to);
        }
        Client::move_unit(from, to);
        board->remove_available_for_moving_cells();
        board->update_board(get_client_state()->m_game_state);
        (*selected_unit)->disable_selection();
        *selected_unit = nullptr;
    }
}

void EventManager::update_game_menu(ButtonType button_type, Window *window) {
    if (button_type == ButtonType::Exit) {
        window->set_is_done();
    } else if (button_type != ButtonType::None) {
        std::cout << "FirstPress is caught!\n";
    }
}
}  // namespace game_view