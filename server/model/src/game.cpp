#include "game.hpp"
#include <vector>
#include "board.hpp"
#include "cell.hpp"

namespace game_model {
board game::get_board() const {
    return m_board;
}

cell game::get_cell(const coordinates &cell_coordinates) const {
    return m_board.get_cell(cell_coordinates);
}

std::vector<cell>
game::get_reachable_cells(const coordinates &cell_coordinates, int user_id) {
    int player_id = (m_players_list[0]->get_id() == user_id ? 0 : 1);
    if (get_cell(cell_coordinates).get_player_index() != player_id)
        return {};
    int max_distance =
        m_players_list[player_id]
            ->get_unit(m_board.get_cell(cell_coordinates).get_unit_index())
            .get_movement_range();
    return m_board.get_reachable_cells(
        cell_coordinates, player_id, max_distance
    );
}

}  // namespace game_model