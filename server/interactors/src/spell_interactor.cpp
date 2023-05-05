#include "spell_interactor.hpp"
#include "cell.hpp"

namespace interactors {
void speller::operator()(
    const game_model::coordinates &cell_coordinates,
    int player_id,
    int spell_id
) {
    m_game.spell(cell_coordinates, player_id, spell_id);
}
}  // namespace interactors