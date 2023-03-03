#ifndef BATTLE_OF_HEROES_GAME_HPP
#define BATTLE_OF_HEROES_GAME_HPP

#include "board.hpp"
#include "event_manager.hpp"
#include "game_menu_bar.hpp"
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
    GameMenuBar m_game_menu_bar;
    EventManager m_event_manager;
};

#endif  // BATTLE_OF_HEROES_GAME_HPP
