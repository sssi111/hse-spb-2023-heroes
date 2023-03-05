#include "choose_interactor.hpp"
#include <vector>
#include "cell.hpp"

namespace interactors {
/* массив клеток */
Chooser::operator()(/* клетка */ current_cell, /* id игрока */ id) {
    std::vector<game_model::Cell> reachable_cells =
        m_game->reachable_cells(current_cell.x, current_cell.y, id);
    return reachable_cells;  // сделать из этого message
}
}  // namespace interactors