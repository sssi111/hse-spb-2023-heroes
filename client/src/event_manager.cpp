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
        // send to server position of our unit to activate unit and get server
        // response with vector of possible steps
        if (*selected_unit != nullptr) {
            (*selected_unit)->disable_selection();
        }
        *selected_unit = *unit;
        (*unit)->set_selection();
    } else if (event_type == CellEventType::SecondPress) {
        std::cout << "SecondPress is caught!\n";
        // send to server position of our unit to deactivate unit
        *selected_unit = nullptr;
        (*unit)->disable_selection();
    } else if (event_type == CellEventType::Move) {
        std::cout << "You wanna move?\n";
        // that's how it will be done with server

        //        auto game_state = get_client_state()->m_game_state;
        //        auto server_unit =
        //            game_state
        //                .game_cells(
        //                    new_position.get_row() * 10 +
        //                    new_position.get_column()
        //                )
        //                .unit();
        //        (*selected_unit)
        //            ->update_unit(
        //                static_cast<UnitType>(server_unit.type_unit()),
        //                new_position, board->get_cell_position(new_position),
        //                board->get_cell_size(), server_unit.sum_of_health(),
        //                server_unit.amount_unit(), server_unit.id_unit(),
        //                server_unit.id_hero()
        //            );
        *unit = *selected_unit;  // guaranteed that *unit is nullptr
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
