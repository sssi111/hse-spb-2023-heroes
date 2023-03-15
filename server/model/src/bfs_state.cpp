#include "bfs_state.hpp"

namespace game_model {
bool bfs_state::is_end() const {
    if (m_coordinates_deque.empty()) {
        return true;
    }
    int x = m_coordinates_deque.front().get_x();
    int y = m_coordinates_deque.front().get_y();
    return m_cell_distance[x][y] > m_max_distance;
}

coordinates bfs_state::get_next_cell() {
    coordinates result = m_coordinates_deque.front();
    m_coordinates_deque.pop_front();
    return result;
}

bool bfs_state::is_good_coordinates(const coordinates &cell_coordinates) const {
    int x = cell_coordinates.get_x();
    int y = cell_coordinates.get_y();
    return x >= 0 && y >= 0 && x < m_board_size.get_x() &&
           y < m_board_size.get_y();
}

int bfs_state::get_cell_distance(const coordinates &cell_coordinates) const {
    int x = cell_coordinates.get_x();
    int y = cell_coordinates.get_y();
    return m_cell_distance[x][y];
}

void bfs_state::set_cell_distance(
    const coordinates &cell_coordinates,
    int distance_new
) {
    int x = cell_coordinates.get_x();
    int y = cell_coordinates.get_y();
    m_cell_distance[x][y] = distance_new;
}

void bfs_state::check_cells_neighbours(const coordinates &cell_coordinates) {
    m_reachable_coordinates.emplace_back(cell_coordinates);
    int current_distance = get_cell_distance(cell_coordinates);
    for (const auto &delta : m_neighbours_coordinates_delta) {
        coordinates neighbour_coordinates = cell_coordinates + delta;
        if (is_good_coordinates(neighbour_coordinates) &&
            get_cell_distance(neighbour_coordinates) == -1) {
            set_cell_distance(neighbour_coordinates, current_distance + 1);
            m_coordinates_deque.emplace_back(neighbour_coordinates);
        }
    }
}

std::vector<coordinates> bfs_state::get_reachable_coordinates() const {
    return m_reachable_coordinates;
}
}  // namespace game_model