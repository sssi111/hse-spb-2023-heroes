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
    int x_size = board_size.get_x();
    int y_size = board_size.get_y();
    int y = (player_index == 0 ? 0 : y_size - 1);
    for (int x = 0; x < x_size; ++x) {
        m_units_list.emplace_back(coordinates{x, y}, player_index, x);
    }
}
}  // namespace game_model