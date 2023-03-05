#ifndef MOVE_INTERACTOR_HPP
#define MOVE_INTERACTOR_HPP

#include <memory>
#include "game.hpp"

namespace interactors {
class Mover {
private:
    std::unique_ptr<game_model::Game> m_game;

public:
    Mover(const game_model::Game &game)
        : m_game(std::make_unique<game_model::Game>(game)) {
    }

    /* игровая доска */
    operator()(/* клетка */ current_cell, /* клетка */ new_cell);
};
}  // namespace interactors

#endif  // MOVE_INTERACTOR_HPP
