#ifndef SPELL_INTERACTOR_HPP
#define SPELL_INTERACTOR_HPP

#include <memory>
#include "game.hpp"

namespace interactors {
class speller {
private:
    game_model::game &m_game;

public:
    explicit speller(game_model::game &current_game_state)
        : m_game(current_game_state) {
    }

    void operator()(
        const game_model::coordinates &cell_coordinates,
        int player_id,
        int spell_id
    );
};
}  // namespace interactors

#endif  // SPELL_INTERACTOR_HPP
