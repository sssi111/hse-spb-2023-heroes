#ifndef BATTLE_OF_HEROES_MENU_BUTTON_HPP
#define BATTLE_OF_HEROES_MENU_BUTTON_HPP
#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "event_manager.hpp"
#include "window.hpp"

namespace game_interface {
class MenuButton {
public:
    MenuButton() = default;
    ~MenuButton() = default;

    MenuButton(
        sf::Vector2f position,
        sf::Vector2f size,
        sf::Color color,
        interface::Fonts font,
        unsigned character_size,
        const std::string &label,
        ButtonType button_type
    );

    ButtonType update(sf::Event event, Window *window);

    void render(sf::RenderWindow *window);

private:
    sf::RectangleShape m_rect;
    sf::Text m_label;
    interface::Button m_button;
    ButtonType m_button_type{ButtonType::None};
};
}  // namespace game_interface

#endif  // BATTLE_OF_HEROES_MENU_BUTTON_HPP
