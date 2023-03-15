#ifndef MODEL_BFS_STATE_HPP
#define MODEL_BFS_STATE_HPP

#include <deque>
#include <vector>
#include "cell.hpp"
#include "coordinates.hpp"

namespace game_model {
class bfs_state {
private:
    std::vector<coordinates> m_reachable_coordinates;
    std::deque<coordinates> m_coordinates_deque;
    std::vector<std::vector<int>> m_cell_distance;
    coordinates m_board_size;
    int m_max_distance;
    const std::vector<coordinates> m_neighbours_coordinates_delta = {
        coordinates(0, 1), coordinates(1, 0), coordinates(0, -1),
        coordinates(-1, 0)};

    [[nodiscard]] bool is_good_coordinates(const coordinates &cell_coordinates
    ) const;
    [[nodiscard]] int get_cell_distance(const coordinates &cell_coordinates
    ) const;
    void
    set_cell_distance(const coordinates &cell_coordinates, int distance_new);

public:
    bfs_state(
        const coordinates &cell_coordinates,
        const coordinates &board_size,
        int max_distance
    )
        : m_coordinates_deque({cell_coordinates}),
          m_cell_distance(
              board_size.get_x(),
              std::vector<int>(board_size.get_y(), -1)
          ),
          m_max_distance(max_distance),
          m_board_size(board_size) {
        m_cell_distance[cell_coordinates.get_x()][cell_coordinates.get_y()] = 0;
    }

    [[nodiscard]] bool is_end() const;
    coordinates get_next_cell();
    void check_cells_neighbours(const coordinates &cell_coordinates);
    [[nodiscard]] std::vector<coordinates> get_reachable_coordinates() const;
};
}  // namespace game_model

#endif  // MODEL_BFS_STATE_HPP
