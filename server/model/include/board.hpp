#ifndef MODEL_BOARD_HPP
#define MODEL_BOARD_HPP

#include <deque>
#include <vector>
#include "cell.hpp"
#include "coordinates.hpp"

namespace game_model {

class board {
private:
    std::vector<std::vector<cell>> m_cells_matrix =
        std::vector<std::vector<cell>>(10, std::vector<cell>(10));
    const coordinates m_size = coordinates(10, 10);

    [[nodiscard]] std::vector<std::reference_wrapper<cell>>
    coordinates_to_cells(const std::vector<coordinates> &coordinates_array);

public:
    board() {
        int x_size = m_size.get_row();
        int y_size = m_size.get_y();
        for (int x = 0; x < x_size; ++x) {
            for (int y = 0; y < y_size; ++y)
                m_cells_matrix[x][y].set_coordinates(coordinates{x, y});
            m_cells_matrix[x][0].set_player_index(0);
            m_cells_matrix[x][y_size - 1].set_player_index(1);
            m_cells_matrix[x][0].set_unit_index(x);
            m_cells_matrix[x][y_size - 1].set_unit_index(x);
        }
    }

    [[nodiscard]] const coordinates &get_size() const;
    [[nodiscard]] cell &get_cell(const coordinates &cell_coordinates);
    [[nodiscard]] std::vector<std::reference_wrapper<cell>>
    get_reachable_cells(coordinates cell_coordinates, int id, int max_distance);
};

}  // namespace game_model

#endif  // MODEL_BOARD_HPP
