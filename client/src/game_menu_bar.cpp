#include "game_menu_bar.hpp"
#include <iostream>
#include "resource_manager.hpp"

namespace game_interface {
GameMenuBar::GameMenuBar(sf::Vector2f wind_size, float menu_height) {
    sf::Vector2f button_size(100.0f, 62.0f);
    sf::Vector2f button_pos(button_size.x, wind_size.y - menu_height / 2);
    float button_padding = (wind_size.x - button_size.x * 4) / 5;

    sf::Vector2f label_size(250.0f, 50.0f);
    m_turn_label.setSize(label_size);
    m_turn_label.setFillColor(sf::Color(71, 78, 50));
    m_turn_label.setOrigin(label_size.x / 2.0f, label_size.y / 2.0f);
    m_turn_label.setPosition(wind_size.x / 2, 50);

    m_data.setFont(game_interface::resource_manager()->load_font(
        interface::Fonts::CaptionFont
    ));
    m_data.setString(sf::String("You turn"));
    m_data.setFillColor(sf::Color::White);
    m_data.setCharacterSize(24);

    sf::FloatRect data_bounds = m_data.getLocalBounds();
    m_data.setOrigin(
        data_bounds.left + data_bounds.width / 2.0f,
        data_bounds.top + data_bounds.height / 2.0f
    );
    m_data.setPosition(wind_size.x / 2, 50);

    m_buttons.resize(3);

    ButtonType button_types[3] = {
        ButtonType::Skip, ButtonType::GiveUp, ButtonType::Menu};

    std::string labels[3];
    labels[0] = "skip";
    labels[1] = "give up";
    labels[2] = "menu";

    m_buttons[0] = MenuButton(
        {wind_size.x * 0.07f + 8 + button_size.x / 2, button_pos.y},
        button_size, sf::Color(71, 78, 50), interface::Fonts::CaptionFont, 22,
        labels[0], button_types[0]
    );
    m_buttons[1] = MenuButton(
        {wind_size.x * 0.07f + 40 + 3 * button_size.x / 2, button_pos.y},
        button_size, sf::Color(71, 78, 50), interface::Fonts::CaptionFont, 22,
        labels[1], button_types[1]
    );
    m_buttons[2] = MenuButton(
        {wind_size.x - wind_size.x * 0.07f - button_size.x / 2 + 4,
         button_pos.y},
        button_size, sf::Color(71, 78, 50), interface::Fonts::CaptionFont, 22,
        labels[2], button_types[2]
    );
}

void GameMenuBar::update(sf::Event event, Window *window) {
    for (auto &button : m_buttons) {
        button.update(event, window);
    }
    if (get_client_state()->m_user.user().id() ==
        get_client_state()->m_game_state.move_turn()) {
        m_data.setString("Your turn");
        sf::FloatRect data_bounds = m_data.getLocalBounds();
        m_data.setOrigin(
            data_bounds.left + data_bounds.width / 2.0f,
            data_bounds.top + data_bounds.height / 2.0f
        );
    } else {
        m_data.setString("Opponent's turn");
        sf::FloatRect data_bounds = m_data.getLocalBounds();
        m_data.setOrigin(
            data_bounds.left + data_bounds.width / 2.0f,
            data_bounds.top + data_bounds.height / 2.0f
        );
    }
}

void GameMenuBar::render(sf::RenderWindow *window) {
    window->draw(m_turn_label);
    window->draw(m_data);
    for (auto &button : m_buttons) {
        button.render(window);
    }
}
}  // namespace game_interface