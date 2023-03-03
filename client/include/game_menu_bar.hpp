#ifndef BATTLE_OF_HEROES_GAME_MENU_BAR_HPP
#define BATTLE_OF_HEROES_GAME_MENU_BAR_HPP

#include <SFML/Graphics.hpp>

struct GameMenuBar {
    GameMenuBar();

    GameMenuBar(sf::Vector2f l_windSize, float l_menu_height);
    ~GameMenuBar();

    bool update(sf::Event event, sf::Window &window);
    void render(sf::RenderWindow &l_window);

private:
    sf::Font m_font;
    sf::Text m_button_labels[4];

    sf::RectangleShape m_rects[4];
    sf::RectangleShape m_background;

    sf::Vector2f m_button_size;
    sf::Vector2f m_button_pos;
    float m_button_padding;
};

#endif // BATTLE_OF_HEROES_GAME_MENU_BAR_HPP
