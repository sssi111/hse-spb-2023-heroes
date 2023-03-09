#include "button.hpp"

Button::Button(sf::Vector2f position, sf::Vector2f size) {
    m_rect.setSize(size);
    m_rect.setOrigin(size.x / 2.0f, size.y / 2.0f);
    m_rect.setPosition(position);
}

bool Button::update(sf::Event event, sf::Window *window) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
        auto rect_size = sf::Vector2i(m_rect.getSize());
        auto rect_position = sf::Vector2i(m_rect.getPosition());
        mouse_position.x += rect_size.x / 2;
        mouse_position.y += rect_size.y / 2;
        if (mouse_position.x >= rect_position.x &&
            mouse_position.x <= rect_position.x + rect_size.x &&
            mouse_position.y >= rect_position.y &&
            mouse_position.y <= rect_position.y + rect_size.y) {
            return true;
        }
    }
    return false;
}
