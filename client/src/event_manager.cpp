#include "event_manager.hpp"
#include <iostream>
#include "client.hpp"

void EventManager::update_cell(
    CellEventType event_type,
    Unit **selected_unit,
    Unit **unit,
    Coords new_position,
    Board *board
) {
    if (event_type == CellEventType::FirstPress) {
        std::cout << "FirstPress is caught!\n";
        namespace_proto::Cell selected_cell;
        selected_cell.set_row(new_position.get_row());
        selected_cell.set_column(new_position.get_column());
        board->add_available_for_moving_cells(Client::select_unit(selected_cell)
        );

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
        // that's how it will be done with server
        board->update_board(get_client_state()->m_game_state);
    }
}

void EventManager::update_game_menu(ButtonType button_type, Window *window) {
    if (button_type == ButtonType::Exit) {
        window->set_is_done();
    } else if (button_type != ButtonType::None) {
        std::cout << "FirstPress is caught!\n";
    }
}
