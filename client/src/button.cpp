#include "button.hpp"

namespace game_view {
    Button::Button(sf::Vector2f position, sf::Vector2f size) {
        m_button.setSize(size);
        m_button.setOrigin(size.x / 2.0f, size.y / 2.0f);
        m_button.setPosition(position);
    }

    bool Button::event_processing(sf::Event event, const sf::Window *window) {
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
            auto button_size = sf::Vector2i(m_button.getSize());
            auto button_position = sf::Vector2i(m_button.getPosition());
            mouse_position.x += button_size.x / 2;
            mouse_position.y += button_size.y / 2;
            if (mouse_position.x >= button_position.x &&
                mouse_position.x <= button_position.x + button_size.x &&
                mouse_position.y >= button_position.y &&
                mouse_position.y <= button_position.y + button_size.y) {
                return true;
            }
        }
        return false;
    }
}