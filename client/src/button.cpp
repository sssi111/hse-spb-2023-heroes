#include "button.hpp"

void Button::draw(sf::RenderWindow *window) {
    window->draw(m_rect);
    window->draw(m_label);
}

Button::Button(
    sf::Vector2f position,
    sf::Vector2f size,
    sf::Color color,
    Fonts font,
    unsigned int character_size,
    const std::string &label
) {
    m_rect.setSize(size);
    m_rect.setFillColor(color);
    m_rect.setOrigin(size.x / 2.0f, size.y / 2.0f);
    m_rect.setPosition(position);

    m_label.setFont(resource_manager()->load_font(font));
    m_label.setString(sf::String(label));
    m_label.setCharacterSize(character_size);

    sf::FloatRect rect = m_label.getLocalBounds();
    m_label.setOrigin(
        rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f
    );

    m_label.setPosition(position);
}

sf::Vector2f Button::get_position() const {
    return m_rect.getPosition();
}

sf::Vector2f Button::get_size() const {
    return m_rect.getSize();
}
