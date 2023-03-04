#ifndef BATTLE_OF_HEROES_EVENT_MANAGER_HPP
#define BATTLE_OF_HEROES_EVENT_MANAGER_HPP

#include "game_menu_bar.hpp"
#include "window.hpp"

class EventManager {
public:
    EventManager(Window *window, GameMenuBar *menu_bar)
        : m_window(window), m_menu_bar(menu_bar){};

    void update(sf::Event event);
    void set_window_is_done();

private:
    Window *m_window;
    GameMenuBar *m_menu_bar;
};

#endif  // BATTLE_OF_HEROES_EVENT_MANAGER_HPP
