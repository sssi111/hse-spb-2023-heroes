#ifndef BATTLE_OF_HEROES_EVENT_MANAGER_HPP
#define BATTLE_OF_HEROES_EVENT_MANAGER_HPP

#include "window.hpp"
#include "game_menu_bar.hpp"

struct EventManager {
    EventManager() : m_window(nullptr), m_menu_bar(nullptr) {};
    EventManager(Window *window, GameMenuBar *menu_bar) : m_window(window), m_menu_bar(menu_bar) {};

    void update(sf::Event event);
    void set_window_is_done();

private:
    Window *m_window;
    GameMenuBar *m_menu_bar;
};

#endif  // BATTLE_OF_HEROES_EVENT_MANAGER_HPP
