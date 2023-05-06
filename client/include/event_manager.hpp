#ifndef BATTLE_OF_HEROES_EVENT_MANAGER_HPP
#define BATTLE_OF_HEROES_EVENT_MANAGER_HPP

#include "board.hpp"
#include "window.hpp"

namespace game_interface {
class EventManager {
public:
    static void update_cell(
        CellEventType event_type,
        Unit **selected_unit,
        Unit **unit,
        Coords clicked_position = {-1, -1},
        Board *board = nullptr
    );
    static void update_game_menu(ButtonType event_type, Window *window);
};
}  // namespace game_interface

#endif  // BATTLE_OF_HEROES_EVENT_MANAGER_HPP
