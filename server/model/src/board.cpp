#include "board.hpp"
#include <vector>
#include "bfs_state.hpp"
#include "cell.hpp"

namespace game_model {
cell &board::get_cell(const coordinates &cell_coordinates) {
    int row = cell_coordinates.get_row();
    int column = cell_coordinates.get_column();
    return m_cells_matrix[row][column];
}

std::vector<std::reference_wrapper<cell>> board::coordinates_to_cells(
    const std::vector<coordinates> &coordinates_array
) {
    std::vector<std::reference_wrapper<cell>> result;
    for (const auto &cell_coordinates : coordinates_array) {
        result.emplace_back(get_cell(cell_coordinates));
    }
    return result;
}

std::vector<std::reference_wrapper<cell>>
board::get_reachable_cells(coordinates cell_coordinates, int max_distance) {
    bfs_state bfs(cell_coordinates, m_size, max_distance);
    while (!bfs.is_end()) {
        coordinates current_cell_coordinates = bfs.get_next_cell();
        if (is_cell_empty(current_cell_coordinates, cell_coordinates))
            bfs.check_cells_neighbours(current_cell_coordinates);
    }
    return coordinates_to_cells(bfs.get_reachable_coordinates());
}

std::vector<std::reference_wrapper<cell>> board::get_attackable_cells(
    coordinates cell_coordinates,
    int player_id,
    int max_distance
) {
    int row_amount = m_size.get_row();
    int column_amount = m_size.get_column();
    for (int row = 0; row < row_amount; ++row) {
        for (int column = 0; column < column_amount; ++column) {
            if ()
        }
    }
}

const coordinates &board::get_size() const {
    return m_size;
}

void board::set_cell_coordinates(int row, int column) {
    m_cells_matrix[row][column].set_coordinates(coordinates{row, column});
}

bool board::is_cell_empty(
    coordinates current_cell_coordinates,
    coordinates start_cell_coordinates
) {
    int cell_player_id = get_cell(current_cell_coordinates).get_player_index();
    int cell_durability = get_cell(current_cell_coordinates).get_durability();
    return (cell_player_id == -1 ||
            current_cell_coordinates == start_cell_coordinates) &&
           cell_durability > 0;
}
}  // namespace game_model