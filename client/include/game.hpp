#ifndef BATTLE_OF_HEROES_GAME_HPP
#define BATTLE_OF_HEROES_GAME_HPP

#include "board.hpp"
#include "window.hpp"
#include "game_menu_bar.hpp"

struct Game {
    Game();
    ~Game();

    void handle_input();
    void update();
    void render();

    Window *get_window();

private:
    Window m_window;
    Board m_board;
    GameMenuBar m_game_menu_bar;

    unsigned int m_menu_height;
};

#endif  // BATTLE_OF_HEROES_GAME_HPP
