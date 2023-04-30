#include "game.hpp"
#include <vector>
#include "board.hpp"
#include "cell.hpp"

namespace game_model {
board &game::get_board() {
    return m_board;
}

cell &game::get_cell(const coordinates &cell_coordinates) {
    return m_board.get_cell(cell_coordinates);
}

std::vector<std::reference_wrapper<cell>>
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

void game::move(
    const coordinates &current_cell_coordinates,
    const coordinates &new_cell_coordinates
) {
    cell &current_cell = get_cell(current_cell_coordinates);
    cell &new_cell = get_cell(new_cell_coordinates);
    int player_index = current_cell.get_player_index();
    int unit_index = current_cell.get_unit_index();
    current_cell.set_player_index(-1);
    current_cell.set_unit_index(-1);
    new_cell.set_player_index(player_index);
    new_cell.set_unit_index(unit_index);
}

}  // namespace game_model
