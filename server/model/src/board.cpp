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

std::vector<std::reference_wrapper<cell>>
board::get_attackable_cells(coordinates cell_coordinates, int max_distance) {
    std::vector<coordinates> attackable_coordinates;
    for (int row = 0; row < m_size.get_row(); ++row)
        for (int column = 0; column < m_size.get_column(); ++column) {
            coordinates attacked_coordinates(row, column);
            if (is_cell_attackable(
                    cell_coordinates, attacked_coordinates, max_distance
                ))
                attackable_coordinates.emplace_back(attacked_coordinates);
        }
    return coordinates_to_cells(attackable_coordinates);
}

bool board::is_cell_attackable(
    const coordinates &attacking,
    const coordinates &attacked,
    int attack_range
) {
    const cell &attacking_cell = get_cell(attacking);
    const cell &attacked_cell = get_cell(attacked);
    return attacked_cell.get_player_index() != -1 &&
           attacked_cell.get_player_index() !=
               attacking_cell.get_player_index() &&
           distance(attacking, attacked) <= attack_range;
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