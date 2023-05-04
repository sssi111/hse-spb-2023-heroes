#include "cell.hpp"
#include <algorithm>

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

void cell::decrease_cell_durability(int damage) {
    m_durability = std::max(0, m_durability - damage);
}

bool cell::is_unit_movable(int player_id) const {
    return m_player_index == player_id;
}

int cell::get_durability() const {
    return m_durability;
}

}  // namespace game_model