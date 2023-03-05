#include "update_interactor.hpp"

namespace interactors {
/* игровая доска */ Updater::operator()() {
    return m_game->get_board();  // сделать из этого message
}
}  // namespace interactors