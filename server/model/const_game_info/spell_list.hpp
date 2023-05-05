#ifndef SPELL_LIST_HPP
#define SPELL_LIST_HPP

#include <vector>
#include "spell.hpp"

namespace const_game_info {
const std::vector<game_model::spell> SPELL_LIST = {game_model::spell(
    0,
    "brake_cell",
    "destroy the selected cell",
    5,
    [](game_model::cell &cell) {
        cell.decrease_cell_durability(cell.get_durability());
    },
    [](const game_model::cell &cell, int player_id) {
        return cell.get_durability() > 0;
    }
)};
}

#endif  // SPELL_LIST_HPP
