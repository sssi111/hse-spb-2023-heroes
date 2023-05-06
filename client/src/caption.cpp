#include "caption.hpp"

namespace menu_view {

Caption::Caption(
    sf::Vector2f position,
    sf::Vector2f size,
    game_view::Fonts font,
    unsigned int character_size,
    const std::string &text,
    PageType current_page
) {
    m_table.setSize(size);
    m_table.setFillColor(sf::Color::Black);
    m_table.setOrigin(size.x / 2.0f, size.y / 2.0f);
    m_table.setPosition(position);

    m_current_page = current_page;

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

PageType Caption::get_current_page() const {
    return m_current_page;
}

void Caption::set_text(const std::string &text) {
    m_data.setString(text);
    sf::FloatRect rect = m_data.getLocalBounds();
    m_data.setOrigin(
        rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f
    );
    m_data.setPosition(m_table.getPosition());
}

void Caption::draw(sf::RenderWindow *window) const {
    window->draw(m_table);
    window->draw(m_data);
}

}  // namespace menu_view