#include "spell_select_interactor.hpp"
#include <vector>
#include "cell.hpp"

namespace interactors {
std::vector<std::reference_wrapper<game_model::cell>>
spell_selecter::operator()(int user_id, int spell_id) {
    std::vector<std::reference_wrapper<game_model::cell>> spellable_cells =
        m_game.get_spellable_cells(user_id, spell_id);
    return spellable_cells;
}
}  // namespace interactors