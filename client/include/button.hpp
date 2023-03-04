#ifndef BATTLE_OF_HEROES_BUTTON_HPP
#define BATTLE_OF_HEROES_BUTTON_HPP
#include <SFML/Graphics.hpp>
#include "resource_manager.hpp"

class Button {
public:
    Button() = default;
    ~Button() = default;

    Button(
        sf::Vector2f position,
        sf::Vector2f size,
        sf::Color color,
        Fonts font,
        unsigned character_size,
        const std::string &label
    );

    sf::Vector2f get_position() const;

    sf::Vector2f get_size() const;

    void draw(sf::RenderWindow *window);

private:
    sf::Text m_label;
    sf::RectangleShape m_rect;
};

#endif  // BATTLE_OF_HEROES_BUTTON_HPP
