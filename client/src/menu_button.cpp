#include "menu_button.hpp"

MenuButton::MenuButton(
    sf::Vector2f position,
    sf::Vector2f size,
    sf::Color color,
    Fonts font,
    unsigned int character_size,
    const std::string &label,
    ButtonType button_type
) {
    m_rect.setSize(size);
    m_rect.setFillColor(color);
    m_rect.setOrigin(size.x / 2.0f, size.y / 2.0f);
    m_rect.setPosition(position);

    m_button = Button(position, size);

    m_button_type = button_type;

    m_label.setFont(resource_manager()->load_font(font));
    m_label.setString(sf::String(label));
    m_label.setCharacterSize(character_size);

    sf::FloatRect rect = m_label.getLocalBounds();
    m_label.setOrigin(
        rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f
    );

    m_label.setPosition(position);
}

ButtonType MenuButton::update(sf::Event event, Window *window) {
    if (m_button.event_processing(event, window->get_render_window())) {
        EventManager::update_game_menu(m_button_type, window);
    }
    return ButtonType::None;
}

void MenuButton::draw(sf::RenderWindow *window) {
    window->draw(m_rect);
    window->draw(m_label);
}
