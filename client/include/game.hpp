#ifndef BATTLE_OF_HEROES_GAME_HPP
#define BATTLE_OF_HEROES_GAME_HPP

#include "board.hpp"
#include "event_manager.hpp"
#include "game_menu_bar.hpp"
#include "window.hpp"

namespace game_view {
class Game {
public:
    Game();
    ~Game() = default;

    void update();
    void render();

    Window *get_window();
    Board *get_board();

private:
    Window m_window;
    sf::Sprite m_background;
    GameMenuBar m_game_menu_bar;
    Board m_board;
};

Game *get_game_state();
}  // namespace game_view

#endif  // BATTLE_OF_HEROES_GAME_HPP
