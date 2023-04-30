#ifndef ATTACK_INTERACTOR_HPP
#define ATTACK_INTERACTOR_HPP

#include <memory>
#include "game.hpp"

namespace interactors {
class attacker {
private:
    game_model::game &m_game;

public:
    explicit attacker(game_model::game &current_game_state)
        : m_game(current_game_state) {
    }

    void operator()(
        const game_model::coordinates &current_cell_coordinates,
        const game_model::coordinates &new_cell_coordinates
    );
};
}  // namespace interactors

#endif  // ATTACK_INTERACTOR_HPP
