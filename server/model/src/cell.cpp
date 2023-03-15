#include "cell.hpp"

namespace game_model {
int cell::get_player_index() const {
    return m_player_index;
}

int cell::get_unit_index() const {
    return m_unit_index;
}

coordinates cell::get_coordinates() const {
    return m_coordinates;
}

void cell::set_player_index(int player_index) {
    m_player_index = player_index;
}

void cell::set_unit_index(int unit_index) {
    m_unit_index = unit_index;
}

void cell::set_coordinates(const coordinates &coordinates_new) {
    m_coordinates = coordinates_new;
}

void cell::move(cell &current_cell, cell &new_cell) {
    new_cell.set_player_index(current_cell.get_player_index());
    new_cell.set_unit_index(current_cell.get_unit_index());
    current_cell.set_player_index(-1);
    current_cell.set_unit_index(-1);
}
}  // namespace game_model