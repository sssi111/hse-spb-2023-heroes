#ifndef BATTLE_OF_HEROES_GAME_MENU_BAR_HPP
#define BATTLE_OF_HEROES_GAME_MENU_BAR_HPP

#include <SFML/Graphics.hpp>
#include "button.hpp"

class GameMenuBar {
public:
    GameMenuBar() = default;

    GameMenuBar(sf::Vector2f l_windSize, float l_menu_height);
    ~GameMenuBar();

    bool update(sf::Event event, sf::Window *window);
    void render(sf::RenderWindow *window);

private:
    sf::RectangleShape m_background;
    std::vector<Button> m_buttons;
    sf::Font m_font;

    sf::Text m_button_labels[4];
    sf::RectangleShape m_rects[4];

    sf::Vector2f m_button_size;
    sf::Vector2f m_button_pos;
    float m_button_padding{};
};

#endif  // BATTLE_OF_HEROES_GAME_MENU_BAR_HPP
