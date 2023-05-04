#include "player.hpp"
#include "unit.hpp"

namespace game_model {
int player::get_id() const {
    return m_id;
}

unit &player::get_unit(int index) {
    return m_units_list[index];
}

void player::set_start_units(int player_index, const board &game_board, const std::vector<int> &troop) {
    coordinates board_size = game_board.get_size();
    int row_amount = board_size.get_row();
    for (int unit : troop) {
        m_units_list.emplace_back(unit);
    }
}
}  // namespace game_model
