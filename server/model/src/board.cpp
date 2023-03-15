#include "board.hpp"
#include <vector>
#include "bfs_state.hpp"
#include "cell.hpp"

namespace game_model {
cell board::get_cell(const coordinates &cell_coordinates) const {
    int x = cell_coordinates.get_x();
    int y = cell_coordinates.get_y();
    return m_cells_matrix[x][y];
}

std::vector<cell> board::coordinates_to_cells(
    const std::vector<coordinates> &coordinates_array
) const {
    std::vector<cell> result;
    for (const auto &cell_coordinates : coordinates_array) {
        result.emplace_back(get_cell(cell_coordinates));
    }
    return result;
}

std::vector<cell> board::get_reachable_cells(
    coordinates cell_coordinates,
    int current_player_id,
    int max_distance
) {
    bfs_state bfs(cell_coordinates, m_size, max_distance);
    while (!bfs.is_end()) {
        coordinates current_cell_coordinates = bfs.get_next_cell();
        int cell_player_id =
            get_cell(current_cell_coordinates).get_player_index();
        if (cell_player_id == -1 || cell_player_id == current_player_id)
            bfs.check_cells_neighbours(cell_coordinates);
    }
    return coordinates_to_cells(bfs.get_reachable_coordinates());
}

coordinates board::get_size() const {
    return m_size;
}
}  // namespace game_model