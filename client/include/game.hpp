#ifndef BATTLE_OF_HEROES_GAME_HPP
#define BATTLE_OF_HEROES_GAME_HPP

#include "board.hpp"
#include "window.hpp"

struct Game {
    Game();
    ~Game();

    void update();
    void render();

    Window *get_window();

private:
    Window m_window;
    Board m_board;
};

#endif  // BATTLE_OF_HEROES_GAME_HPP
