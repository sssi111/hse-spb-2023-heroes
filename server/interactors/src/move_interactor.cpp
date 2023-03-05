#include "move_interactor.hpp"
#include "cell.hpp"

namespace interactors {
/* игровая доска */
Mover::operator()(/* клетка */ current_cell, /* клетка */ new_cell) {
    game_model::Cell &current_model_cell =
        m_game->get_cell(current_cell.x, current_cell.y);
    game_model::Cell &new_model_cell = m_game->get_cell(new_cell.x, new_cell.y);
    game_model::move(current_model_cell, new_model_cell);
    return m_game->get_board();  // сделать из этого message
}
}  // namespace interactors