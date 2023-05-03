#include "button.hpp"

#include <iostream>
namespace game_view {
Button::Button(sf::Vector2f position, sf::Vector2f size) {
    m_button.setSize(size);
    m_button.setOrigin(size.x / 2.0f, size.y / 2.0f);
    m_button.setPosition(position);
}

CellEventType Button::event_processing(sf::Event event, const sf::Window *window) {
    sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
    std::cout << mouse_position.x << ' ' << mouse_position.y << " - mouse\n";
    auto button_size = sf::Vector2i(m_button.getSize());
    auto button_position = sf::Vector2i(m_button.getPosition());
    std::cout << button_position.x << ' ' << button_position.y << " - button\n";
    mouse_position.x += button_size.x / 2;
    mouse_position.y += button_size.y / 2;
    if (mouse_position.x >= button_position.x &&
        mouse_position.x <= button_position.x + button_size.x &&
        mouse_position.y >= button_position.y &&
        mouse_position.y <= button_position.y + button_size.y) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            return CellEventType::FirstPress;
        }
        return CellEventType::Targeting;
    }
    return CellEventType::Nothing;
}
}  // namespace game_view