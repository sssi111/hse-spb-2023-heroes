#include "event_manager.hpp"
#include <iostream>

void EventManager::update_cell(
    CellEventType event_type,
    Coords prev_position,
    Coords new_position
) {
    if (event_type == CellEventType::Press) {
        std::cout << "Press is caught!\n";
    } else if (event_type == CellEventType::Move) {
        std::cout << "You wanna move?\n";
    }
}

void EventManager::update_game_menu(ButtonType button_type, Window *window) {
    if (button_type == ButtonType::Exit) {
        window->set_is_done();
    } else if (button_type != ButtonType::None) {
        std::cout << "Press is caught!\n";
    }
}
