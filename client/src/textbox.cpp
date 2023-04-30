#include "textbox.hpp"

namespace menu_view {
TextBox::TextBox(
    sf::Vector2f position,
    sf::Vector2f size,
    game_view::Fonts font,
    unsigned int character_size
) {
    m_rect.setSize(size);
    m_rect.setFillColor(sf::Color::White);
    m_rect.setOrigin(size.x / 2.0f, size.y / 2.0f);
    m_rect.setPosition(position);

    m_button = game_view::Button(position, size);

    m_label.setFont(game_view::resource_manager()->load_font(font));
    m_label.setFillColor(sf::Color::Red);
    m_label.setCharacterSize(character_size);

    sf::FloatRect rect = m_label.getLocalBounds();
    m_label.setOrigin(
        rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f
    );

    m_label.setPosition(position.x - size.x / 2 + character_size /2 , position.x - size.y / 2 + character_size / 2);
    m_is_active = true;
}


game_view::ButtonType TextBox::update(sf::Event event, game_view::Window *window) {
    if (m_button.event_processing(event, window->get_render_window())) {
        m_is_active = true;
    } else if (event.type == sf::Event::TextEntered && event.text.unicode != 10) {
        m_input += event.text.unicode;
        m_label.setString(m_input);
    } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        std::cout << "Got from you: " << m_input.toAnsiString() << "\n";
        m_input.clear();
        m_label.setString(m_input);
    }
    return game_view::ButtonType::None;
}

void TextBox::draw(sf::RenderWindow *window) const {
    window->draw(m_rect);
    window->draw(m_label);
}
}  // namespace game_view