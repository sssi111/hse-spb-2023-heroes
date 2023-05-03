#ifndef BATTLE_OF_HEROES_BUTTON_HPP
#define BATTLE_OF_HEROES_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "resource_manager.hpp"

namespace game_view {
    class Button {
    public:
        Button() = default;
        Button(sf::Vector2f position, sf::Vector2f size);

        CellEventType event_processing(sf::Event event, const sf::Window *window);

    private:
        sf::RectangleShape m_button;
    };
}
#endif  // BATTLE_OF_HEROES_BUTTON_HPP
