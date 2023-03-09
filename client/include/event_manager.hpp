#ifndef BATTLE_OF_HEROES_EVENT_MANAGER_HPP
#define BATTLE_OF_HEROES_EVENT_MANAGER_HPP

#include "board.hpp"
#include "game_menu_bar.hpp"
#include "window.hpp"

class EventManager {
public:
    static void update_cell(
        CellEventType event_type,
        Coords prev_position,
        Coords new_position = {-1, -1}
    );
    static void update_game_menu(ButtonType event_type, Window *window);
};

#endif  // BATTLE_OF_HEROES_EVENT_MANAGER_HPP
