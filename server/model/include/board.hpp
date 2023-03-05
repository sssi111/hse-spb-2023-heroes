#ifndef MODEL_BOARD_HPP
#define MODEL_BOARD_HPP

#include <vector>
#include "cell.hpp"
#include "coordinates.hpp"

namespace game_model {

struct Board {
private:
    std::vector<std::vector<Cell>> m_cells_matrix;
    const std::vector<Coordinates> m_delta = {
        Coordinates(0, 1), Coordinates(1, 0), Coordinates(0, -1),
        Coordinates(-1, 0)};
    const Coordinates m_size = Coordinates(10, 10);

public:
    Cell &get_cell(Coordinates cell_coordinates) const;
    std::vector<Cell> reachable_cells(Coordinates cell_coordinates, int id)
        const;
};

}  // namespace game_model

#endif  // MODEL_BOARD_HPP
