#ifndef BATTLE_OF_HEROES_BUTTON_HPP
#define BATTLE_OF_HEROES_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "resource_manager.hpp"

namespace interface {
class Button {
public:
    Button() = default;
    ~Button() = default;
    Button(sf::Vector2f position, sf::Vector2f size);

    game_interface::CellEventType
    handling_event(sf::Event event, const sf::Window *window);

private:
    sf::RectangleShape m_button;
};
}  // namespace interface
#endif  // BATTLE_OF_HEROES_BUTTON_HPP
