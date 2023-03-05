#ifndef CHOOSE_INTERACTOR_HPP
#define CHOOSE_INTERACTOR_HPP

#include <memory>
#include "game.hpp"

namespace interactors {
class Chooser {
private:
    std::unique_ptr<game_model::Game> m_game;

public:
    Chooser(const game_model::Game &game)
        : m_game(std::make_unique<game_model::Game>(game)) {
    }

    /* массив клеток */
    operator()(/* клетка */ current_cell);
};
}  // namespace interactors

#endif  // CHOOSE_INTERACTOR_HPP