#ifndef BATTLE_OF_HEROES_GAME_MENU_BAR_HPP
#define BATTLE_OF_HEROES_GAME_MENU_BAR_HPP

#include <SFML/Graphics.hpp>
#include "menu_button.hpp"
#include "window.hpp"

class MenuButton;

class GameMenuBar {
public:
    GameMenuBar(sf::Vector2f wind_size, float menu_height);
    ~GameMenuBar() = default;

    void update(sf::Event event, Window *window);
    void render(sf::RenderWindow *window);

private:
    sf::RectangleShape m_background;
    std::vector<MenuButton> m_buttons{4};
};

#endif  // BATTLE_OF_HEROES_GAME_MENU_BAR_HPP
