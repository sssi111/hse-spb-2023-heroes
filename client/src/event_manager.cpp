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
        *selected_unit = *unit;
    } else if (event_type == CellEventType::SecondPress) {
        std::cout << "SecondPress is caught!\n";
        *selected_unit = nullptr;
    } else if (event_type == CellEventType::Move) {
        std::cout << "You wanna move?\n";
        // send(selected_unit.get_coords(), new_position)
        // decrease_cell_strength()
        *unit = *selected_unit;
        board->move_unit(selected_unit, new_position);
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
