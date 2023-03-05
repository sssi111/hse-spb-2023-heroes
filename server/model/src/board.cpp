#include "board.hpp"
#include <deque>
#include <vector>
#include "cell.hpp"

namespace game_model {
Cell &Board::get_cell(Coordinates cell_coordinates) const {
    int x = cell_coordinates.get_x();
    int y = cell_coordinates.get_y();
    return m_cells_matrix[x][y];
}

std::vector<Cell> Board::reachable_cells(
    Coordinates cell_coordinates,
    int id,
    int max_distance
) const {
    int x = cell_coordinates.get_x();
    int y = cell_coordinates.get_y();
    std::vector<Cell> result;
    std::deque<Coordinates> coordinates_bfs_deque = {cell_coordinates};
    std::deque<int> distance_bfs_deque = {0};
    while (!distance_bfs_deque.empty() &&
           distance_bfs_deque.front() <= max_distance) {
    }
}
}  // namespace game_model