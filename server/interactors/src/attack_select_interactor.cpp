#include "attack_select_interactor.hpp"
#include <vector>
#include "cell.hpp"

namespace interactors {
std::vector<std::reference_wrapper<game_model::cell>>
attack_selecter::operator()(
    const game_model::coordinates &current_cell_coordinates,
    int user_id
) {
    std::vector<std::reference_wrapper<game_model::cell>> attackable_cells =
        m_game.get_attackable_cells(current_cell_coordinates, user_id);
    return attackable_cells;
}
}  // namespace interactors