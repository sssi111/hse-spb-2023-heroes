#include "cell.hpp"

namespace game_model {
int Cell::get_player_index() const {
    return m_player_index();
}

int Cell::get_unit_index() const {
    return m_unit_index();
}

void Cell::set_player_index(int player_index) {
    m_player_index = player_index;
}

void Cell::set_unit_index(int unit_index) {
    m_unit_index = unit_index;
}

void move(Cell &current_cell, Cell &new_cell) {
    new_cell.set_player_index(current_cell.get_player_index());
    new_cell.set_unit_index(current_cell.get_unit_index());
    current_cell.set_player_index(-1);
    current_cell.set_unit_index(-1);
}
}  // namespace game_model