#include "game_menu_bar.hpp"
#include <iostream>
#include "resource_manager.hpp"

namespace game_view {
GameMenuBar::GameMenuBar(sf::Vector2f wind_size, float menu_height) {
    sf::Vector2f button_size(100.0f, 62.0f);
    sf::Vector2f button_pos(button_size.x, wind_size.y - menu_height / 2);
    float button_padding = (wind_size.x - button_size.x * 4) / 5;  // 4px.

    ButtonType button_types[4] = {
        ButtonType::Play, ButtonType::Pass, ButtonType::Menu, ButtonType::Exit};

    std::string labels[4];
    labels[0] = "PLAY";
    labels[1] = "PASS";
    labels[2] = "MENU";
    labels[3] = "EXIT";

    m_background.setPosition(0, wind_size.y - menu_height);
    m_background.setSize(sf::Vector2f(wind_size.x, menu_height));
    m_background.setFillColor(sf::Color::Black);

    for (int i = 0; i < 4; ++i) {
        sf::Vector2f button_position(
            button_padding + button_size.x / 2 +
                i * (button_size.x + button_padding),
            button_pos.y
        );
        m_buttons[i] = MenuButton(
            button_position, button_size, sf::Color(139, 69, 19),
            Fonts::Montserrat, 24, labels[i], button_types[i]
        );
    }
}

void GameMenuBar::update(sf::Event event, Window *window) {
    for (auto &button : m_buttons) {
        button.update(event, window);
    }
}

void GameMenuBar::render(sf::RenderWindow *window) {
    window->draw(m_background);
    for (int i = 0; i < 4; ++i) {
        m_buttons[i].draw(window);
    }
}
}  // namespace game_view