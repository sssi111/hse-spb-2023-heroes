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
    int column_amount = board_size.get_column();
    int column = (player_index == 0 ? 0 : column_amount - 1);
    for (int row = 0; row < row_amount; ++row) {
        m_units_list.emplace_back(coordinates{row, column}, player_index, row);
    }
}
}  // namespace game_model