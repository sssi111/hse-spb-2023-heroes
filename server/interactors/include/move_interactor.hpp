#ifndef MOVE_INTERACTOR_HPP
#define MOVE_INTERACTOR_HPP

#include <memory>
#include "game.hpp"

namespace interactors {
class mover {
private:
    game_model::game &m_game;

public:
    explicit mover(game_model::game &current_game_state)
        : m_game(current_game_state) {
    }

    void operator()(
        const game_model::coordinates &current_cell_coordinates,
        const game_model::coordinates &new_cell_coordinates
    );
};
}  // namespace interactors

#endif  // MOVE_INTERACTOR_HPP
