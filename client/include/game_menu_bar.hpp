#ifndef BATTLE_OF_HEROES_GAME_MENU_BAR_HPP
#define BATTLE_OF_HEROES_GAME_MENU_BAR_HPP

#include <SFML/Graphics.hpp>
#include "button.hpp"

class GameMenuBar {
public:
    GameMenuBar(sf::Vector2f wind_size, float menu_height);
    ~GameMenuBar() = default;

    bool update(sf::Event event, sf::Window *window);
    void render(sf::RenderWindow *window);

private:
    sf::RectangleShape m_background;
    std::vector<Button> m_buttons{4};
};

#endif  // BATTLE_OF_HEROES_GAME_MENU_BAR_HPP
