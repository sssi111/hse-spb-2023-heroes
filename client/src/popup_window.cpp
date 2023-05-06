#include "popup_window.hpp"

namespace interface {
PopUpWindow::PopUpWindow(
    sf::Vector2f position,
    sf::Vector2f size,
    game_view::Fonts font,
    unsigned int character_size,
    const std::string &text
) {
    m_table.setSize(size);
    m_table.setFillColor(sf::Color::Black);
    m_table.setPosition(position);

    m_data.setFont(game_view::resource_manager()->load_font(font));
    m_data.setString(sf::String(text));
    m_data.setFillColor(sf::Color::White);
    m_data.setCharacterSize(character_size);

    sf::FloatRect rect = m_data.getLocalBounds();
    m_data.setOrigin(
        rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f
    );

    m_data.setPosition(position);
}

void PopUpWindow::update(
    const std::string &text,
    game_view::CellEventType event_type,
    const sf::Window *window
) {
    if (event_type == game_view::CellEventType::Targeting) {
        m_is_active = true;
        auto mouse_position = sf::Mouse::getPosition(*window);
        m_data.setPosition(mouse_position.x, mouse_position.y);
        m_table.setPosition(mouse_position.x, mouse_position.y);
        m_data.setString(text);
    } else {
        m_is_active = false;
    }
}

void PopUpWindow::draw(sf::RenderWindow *window) {
    if (m_is_active) {
        window->draw(m_table);
        window->draw(m_data);
    }
}
}  // namespace interface
