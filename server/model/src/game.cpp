#include "game.hpp"
#include <vector>
#include "board.hpp"
#include "cell.hpp"

namespace game_model {

bool Game::is_can_move(int player_index) {
    return player_index == m_current_player_index;
}

void Game::change_player() {
    m_current_player ^= 1;
}

Board Game::get_board() const {
    return m_board;
}

Cell &Game::get_cell(Coordinates cell_coordinates) const {
    int x = cell_coordinates.get_x();
    int y = cell_coordinates.get_y();
    return m_board.get_cell(x, y);
}

std::vector<Cell>
Game::reachable_cells(Coordinates cell_coordinates, int user_id) const {
    int x = cell_coordinates.get_x();
    int y = cell_coordinates.get_y();
    int player_id = (m_players_list[0]->get_id() == user_id ? 0 : 1);
    if (get_cell(x, y).get_player_index() != player_id) {
        return std::vector<Cell>();
    }
    int max_distance = m_players_list[player_id]
                           ->get_unit(m_board.get_cell(x, y).get_unit_index())
                           .get_movement_range();
    return m_board.reachable_cells(cell_coordinates, player_id, max_distance);
}

}  // namespace game_model