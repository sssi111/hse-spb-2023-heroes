#ifndef BATTLE_OF_HEROES_GAME_HPP
#define BATTLE_OF_HEROES_GAME_HPP

#include "board.hpp"
#include "event_manager.hpp"
#include "game_menu_bar.hpp"
#include "window.hpp"

class Game {
public:
    Game()
        : m_window("Battle of Heroes and Villains", sf::Vector2u(1920, 1080)),
          m_game_menu_bar(sf::Vector2f(1920, 1080), 100),
          m_board(sf::Vector2i(1920, 1080 - 100)
          )  // '- 100' is subtraction of menu_height
          {};
    ~Game() = default;

    void update();
    void render();

    Window *get_window();

private:
    Window m_window;
    GameMenuBar m_game_menu_bar;
    Board m_board;
};

#endif  // BATTLE_OF_HEROES_GAME_HPP
