#ifndef BATTLE_OF_HEROES_POPUP_WINDOW_HPP
#define BATTLE_OF_HEROES_POPUP_WINDOW_HPP

#include <SFML/Graphics.hpp>
#include "button.hpp"

namespace interface {
class PopUpWindow {
public:
    PopUpWindow() = default;
    PopUpWindow(
        sf::Vector2f position,
        sf::Vector2f size,
        interface::Fonts font,
        unsigned int character_size,
        const std::string &text
    );

    void update(
        const std::string &text,
        game_interface::CellEventType event_type,
        const sf::Window *window
    );
    void render(sf::RenderWindow *window);

private:
    sf::RectangleShape m_table;
    sf::Text m_data;
    Button m_button;
    bool m_is_active{false};
};
}  // namespace interface

#endif  // BATTLE_OF_HEROES_POPUP_WINDOW_HPP
