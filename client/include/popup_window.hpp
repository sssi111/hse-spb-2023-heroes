#ifndef BATTLE_OF_HEROES_POPUP_WINDOW_HPP
#define BATTLE_OF_HEROES_POPUP_WINDOW_HPP

#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "enum_classes_fwd.hpp"

namespace interface {
class PopUpWindow {
public:
    PopUpWindow() = default;
    PopUpWindow(
        sf::Vector2f position,
        sf::Vector2f size,
        game_view::Fonts font,
        unsigned int character_size,
        const std::string &text
    );

    void update(
        const std::string &text,
        game_view::CellEventType event_type,
        const sf::Window *window
    );

    void draw(sf::RenderWindow *window);

private:
    sf::RectangleShape m_table;
    sf::Text m_data;
    game_view::Button m_button;
    bool m_is_active{false};
};
}  // namespace interface

#endif  // BATTLE_OF_HEROES_POPUP_WINDOW_HPP
