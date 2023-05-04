#include "spell_select_interactor.hpp"
#include <vector>
#include "cell.hpp"

namespace interactors {
std::vector<std::reference_wrapper<game_model::cell>>
spell_selecter::operator()(
    const game_model::coordinates &current_cell_coordinates,
    int user_id
) {
    std::vector<std::reference_wrapper<game_model::cell>> reachable_cells =
        m_game.get_spellable_cells(current_cell_coordinates, user_id);
    return reachable_cells;
}
}  // namespace interactors