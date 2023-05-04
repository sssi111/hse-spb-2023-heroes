#ifndef SPELL_SELECT_INTERACTOR_HPP
#define SPELL_SELECT_INTERACTOR_HPP

#include <memory>
#include "game.hpp"

namespace interactors {
class spell_selecter {
private:
    game_model::game &m_game;

public:
    explicit spell_selecter(game_model::game &current_game_state)
        : m_game(current_game_state) {
    }

    std::vector<std::reference_wrapper<game_model::cell>> operator()(
        const game_model::coordinates &current_cell_coordinates,
        int user_id
    );
};
}  // namespace interactors

#endif  // SPELL_SELECT_INTERACTOR_HPP