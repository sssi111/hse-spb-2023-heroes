#include "game_menu_bar.hpp"
#include <iostream>
#include "resource_manager.hpp"

namespace game_interface {
GameMenuBar::GameMenuBar(sf::Vector2f wind_size, float menu_height) {
    sf::Vector2f button_size{100.0f, 60.0f};
    sf::Vector2f button_pos(button_size.x, wind_size.y - menu_height / 2);

    sf::Vector2f label_size{250.0f, 50.0f};
    m_turn_label.setSize(label_size);
    m_turn_label.setFillColor(sf::Color(71, 78, 50));
    m_turn_label.setOrigin(label_size.x / 2.0f, label_size.y / 2.0f);
    m_turn_label.setPosition(wind_size.x / 2, 40.0f);

    m_mana.setFont(game_interface::resource_manager()->load_font(
        interface::Fonts::CaptionFont
    ));
    m_mana.setFillColor(sf::Color::White);
    m_mana.setCharacterSize(24);
    m_mana.setPosition({20.0f, 50.0f});
    m_mana.setString("");

    m_opponent_mana.setFont(game_interface::resource_manager()->load_font(
        interface::Fonts::CaptionFont
    ));
    m_opponent_mana.setFillColor(sf::Color::White);
    m_opponent_mana.setCharacterSize(24);
    m_opponent_mana.setPosition({1900.0f, 50.0f});
    m_opponent_mana.setString("");

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
    m_data.setPosition(wind_size.x / 2, 40.0f);

    m_buttons.resize(3);

    ButtonType button_types[3] = {
        ButtonType::Skip, ButtonType::GiveUp, ButtonType::Menu};

    std::string labels[3];
    labels[0] = "skip";
    labels[1] = "give up";
    labels[2] = "menu";

    m_buttons[0] = MenuButton(
        {wind_size.x * 0.07f + button_size.x / 2, button_pos.y},
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

    m_spells_amount = get_client_state()->m_hero.spells_size();
    sf::Vector2f spell_size{130, 80};
    float distance = 100.0f;
    float start_position_y = wind_size.y / 2 -
                             spell_size.y / 2 * (m_spells_amount % 2) -
                             (m_spells_amount / 2) * (spell_size.y + distance);

    m_spells.resize(m_spells_amount);
    for (int spell_id = 0; spell_id < m_spells_amount; spell_id++) {
        auto current_spell = get_client_state()->m_hero.spells(spell_id);
        m_spells[spell_id] = Spell({67.0f, start_position_y  + spell_id * (spell_size.y + distance)}, spell_size,
                                   current_spell);
    }
}

void GameMenuBar::update_turn(const std::string &new_label) {
    m_data.setString(new_label);
    sf::FloatRect data_bounds = m_data.getLocalBounds();
    m_data.setOrigin(
        data_bounds.left + data_bounds.width / 2.0f,
        data_bounds.top + data_bounds.height / 2.0f
    );
}

void GameMenuBar::update(sf::Event event, Window *window) {
    if (m_buttons[0].update(event, window) == ButtonType::Skip) {
        Client::skip_turn();
    }
    if (m_buttons[1].update(event, window) == ButtonType::GiveUp) {
        Client::end_session();
    }
    if (m_buttons[2].update(event, window) == ButtonType::Menu) {
        // menu
    }

    m_mana.setString(std::to_string(Client::get_mana()));
    m_opponent_mana.setString(std::to_string(Client::get_opponent_mana()));

    for (auto &spell : m_spells) {
        spell.update(event, window);
    }
    if (get_client_state()->m_game_state.move_turn() == 0) {
        update_turn("Nobody's turn");
    } else if (get_client_state()->m_user.user().id() ==
        get_client_state()->m_game_state.move_turn()) {
        update_turn("Your turn");
    } else {
        update_turn("Opponent's turn");
    }
    if (get_client_state()->m_opponent.type() == -1 &&
        get_client_state()->m_game_state.move_turn() != 0) {
        Client::get_opponent();
        m_opponents_spells_amount =
            get_client_state()->m_opponent.spells_size();
        sf::Vector2f spell_size{130, 80};
        float distance = 100.0f;
        float start_position_y = 540.0f -
                                 spell_size.y / 2 * (m_opponents_spells_amount % 2) -
                                 (m_opponents_spells_amount / 2) * (spell_size.y + distance);

        m_opponents_spells.resize(m_opponents_spells_amount);
        for (int spell_id = 0; spell_id < m_opponents_spells_amount; spell_id++) {
            auto current_spell = get_client_state()->m_opponent.spells(spell_id);
            m_opponents_spells[spell_id] = Spell({1853.0f, start_position_y  + spell_id * (spell_size.y + distance)}, spell_size,
                                       current_spell);
        }
    }
}

void GameMenuBar::render(sf::RenderWindow *window) {
    window->draw(m_turn_label);
    window->draw(m_mana);
    window->draw(m_opponent_mana);
    window->draw(m_data);
    for (auto &button : m_buttons) {
        button.render(window);
    }
    for (auto &spell : m_spells) {
        spell.render(window);
    }
    for (auto &spell : m_opponents_spells) {
        spell.render(window);
    }
}

void GameMenuBar::apply_spell() {
    for (auto &spell : m_spells) {
        spell.set_name();
    }
    m_mana.setString(std::to_string(Client::get_mana()));
    m_opponent_mana.setString(std::to_string(Client::get_opponent_mana()));
}
}  // namespace game_interface