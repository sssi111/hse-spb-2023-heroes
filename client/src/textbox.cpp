#include "textbox.hpp"

namespace menu_view {
TextBox::TextBox(
    sf::Vector2f position,
    sf::Vector2f size,
    game_view::Fonts font,
    unsigned int character_size,
    bool is_active
) {
    m_table.setSize(size);
    m_table.setFillColor(sf::Color::White);
    m_table.setOrigin(size.x / 2.0f, size.y / 2.0f);
    m_table.setPosition(position);

    m_button = game_view::Button(position, size);

    m_label.setFont(game_view::resource_manager()->load_font(font));
    m_label.setFillColor(sf::Color::Black);
    m_label.setCharacterSize(character_size);

    sf::FloatRect rect = m_label.getLocalBounds();
    m_label.setOrigin(
        rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f
    );

    m_label.setPosition(
        position.x - size.x / 2 + character_size / 2,
        position.y - size.y / 2 + character_size / 2
    );
    m_is_active = is_active;
}

bool TextBox::is_active() const {
    return m_is_active;
}

bool TextBox::is_showed() const {
    return m_is_showed;
}

std::string TextBox::get_data() const {
    return m_data;
}

void TextBox::activate() {
    m_is_active = false;
}

void TextBox::hide_data() {
    m_is_showed = false;
    m_label.setString(m_hidden_data);
}

void TextBox::show_data() {
    m_is_showed = true;
    m_label.setString(m_data);
}

void TextBox::clear() {
    m_data = "";
    m_label.setString(m_data);
}

bool TextBox::update(sf::Event event, game_view::Window *window) {
    bool result = false;
    if (m_button.event_processing(event, window->get_render_window()) == game_view::CellEventType::FirstPress) {
        m_is_active = true;
        result = true;
    } else if (m_is_active && event.type == sf::Event::TextEntered && event.text.unicode != 10 &&  event.text.unicode != 8) {
        m_data += event.text.unicode;
        m_hidden_data += '*';
    } else if (m_is_active && event.type == sf::Event::TextEntered && event.text.unicode == 8) {
        if (!m_data.isEmpty()) {
            m_data.erase(m_data.getSize() - 1, 1);
            m_hidden_data.erase(m_hidden_data.getSize() - 1, 1);
        }
    }
    if (m_is_showed) {
        m_label.setString(m_data);
    } else {
        m_label.setString(m_hidden_data);
    }
    return result;
}

void TextBox::draw(sf::RenderWindow *window) const {
    window->draw(m_table);
    window->draw(m_label);
}
}  // namespace menu_view