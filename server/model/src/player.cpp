#include "player.hpp"
#include "unit.hpp"

namespace game_model {
int player::get_id() const {
    return m_id;
}

unit &player::get_unit(int index) {
    return m_units_list[index];
}

void player::set_start_units(int player_index, const board &game_board) {
    coordinates board_size = game_board.get_size();
    int row_amount = board_size.get_row();
    for (int row = 0; row < row_amount; ++row) {
        m_units_list.emplace_back(1 + row % 2);
    }
}

void player::decrease_mana(int cost) {
    m_mana = std::max(0, m_mana - cost);
}

int player::get_mana() const {
    return m_mana;
}
}  // namespace game_model