#include <game.hpp>

namespace game_model {

bool Game::can_move(int player_index) {
    return player_index == m_current_player_index;
}

void Game::change_player() {
    m_current_player ^= 1;
}

}  // namespace game_model