#include "attack_interactor.hpp"
#include "cell.hpp"

namespace interactors {
void attacker::operator()(
    const game_model::coordinates &current_cell_coordinates,
    const game_model::coordinates &new_cell_coordinates
) {
    m_game.attack(current_cell_coordinates, new_cell_coordinates);
}
}  // namespace interactors