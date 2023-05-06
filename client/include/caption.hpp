#ifndef BATTLE_OF_HEROES_CAPTION_HPP
#define BATTLE_OF_HEROES_CAPTION_HPP

#include <SFML/Graphics.hpp>
#include "event_manager.hpp"

namespace menu_view {
class Caption {
public:
    Caption() = default;
    ~Caption() = default;

    Caption(
        sf::Vector2f position,
        sf::Vector2f size,
        game_view::Fonts font,
        unsigned character_size,
        const std::string &text,
        PageType m_current_page
    );

    PageType get_current_page() const;
    void set_text(const std::string &text);
    void draw(sf::RenderWindow *window) const;

private:
    sf::RectangleShape m_table;
    sf::Text m_data;
    PageType m_current_page{PageType::Game};
};
}  // namespace menu_view

#endif  // BATTLE_OF_HEROES_CAPTION_HPP
