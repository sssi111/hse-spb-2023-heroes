#ifndef BATTLE_OF_HEROES_TEXTBOX_HPP
#define BATTLE_OF_HEROES_TEXTBOX_HPP

#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "event_manager.hpp"
#include "resource_manager.hpp"
#include "window.hpp"

namespace menu_view {
class TextBox {
public:
    TextBox() = default;
    ~TextBox() = default;

    TextBox(
        sf::Vector2f position,
        sf::Vector2f size,
        game_view::Fonts font,
        unsigned character_size
    );

    game_view::ButtonType update(sf::Event event, game_view::Window *window);

    void draw(sf::RenderWindow *window) const;

private:
    sf::RectangleShape m_rect;
    sf::String m_input;
    bool m_is_active{false};
    sf::Text m_label;
    game_view::Button m_button;
};
}  // namespace menu_view

#endif  // HSE_SPB_2023_HEROES_TEXTBOX_HPP
