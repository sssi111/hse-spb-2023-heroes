#ifndef MODEL_BOARD_HPP
#define MODEL_BOARD_HPP

#include <cell.hpp>
#include <vector>

namespace game_model {

struct Board {
private:
    std::vector<std::vector<Cell>> m_cells_matrix;
};

}  // namespace game_model

#endif  // MODEL_BOARD_HPP
