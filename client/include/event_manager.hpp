#ifndef BATTLE_OF_HEROES_EVENT_MANAGER_HPP
#define BATTLE_OF_HEROES_EVENT_MANAGER_HPP

#include "board.hpp"
#include "game_menu_bar.hpp"
#include "window.hpp"

class EventManager {
public:
    static void update_cell(
        CellEventType event_type,
        Unit **selected_unit,
        Unit **unit,
        Coords new_position = {-1, -1},
        Board *board = nullptr
    );
    static void update_game_menu(ButtonType event_type, Window *window);
};

#endif  // BATTLE_OF_HEROES_EVENT_MANAGER_HPP