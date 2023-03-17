#include "event_manager.hpp"
#include <iostream>

void EventManager::update_cell(
    CellEventType event_type,
    Unit **selected_unit,
    Unit **unit,
    Coords new_position,
    Board *board
) {
    if (event_type == CellEventType::FirstPress) {
        std::cout << "FirstPress is caught!\n";
        if (*selected_unit != nullptr) {
            (*selected_unit)->disable_selection();
        }
        *selected_unit = *unit;
        (*unit)->set_selection();
    } else if (event_type == CellEventType::SecondPress) {
        std::cout << "SecondPress is caught!\n";
        *selected_unit = nullptr;
        (*unit)->disable_selection();
    } else if (event_type == CellEventType::Move) {
        std::cout << "You wanna move?\n";
        *unit = *selected_unit;
        board->move_unit(selected_unit, new_position);
        board->decrease_cell_strength(new_position);
        *selected_unit = nullptr;
        (*unit)->disable_selection();
    }
}

void EventManager::update_game_menu(ButtonType button_type, Window *window) {
    if (button_type == ButtonType::Exit) {
        window->set_is_done();
    } else if (button_type != ButtonType::None) {
        std::cout << "FirstPress is caught!\n";
    }
}
