#ifndef UPDATE_INTERACTOR_HPP
#define UPDATE_INTERACTOR_HPP

#include <memory>
#include "game.hpp"

namespace interactors {
class Updater {
private:
    std::unique_ptr<game_model::Game> m_game;

public:
    Updater(const game_model::Game &game)
        : m_game(std::make_unique<game_model::Game>(game)) {
    }

    /* игровая доска */ operator()();
};
}  // namespace interactors

#endif  // UPDATE_INTERACTOR_HPP
