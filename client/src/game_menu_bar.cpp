#include "game_menu_bar.hpp"
#include <iostream>
#include "resource_manager.hpp"

GameMenuBar::GameMenuBar(sf::Vector2f l_wind_size, float l_menu_height) {
    m_font.loadFromFile(source_dir + "Montserrat-SemiBold.otf");

    m_button_size = sf::Vector2f(100.0f, 62.0f);
    m_button_pos =
        sf::Vector2f(m_button_size.x, l_wind_size.y - l_menu_height / 2);
    m_button_padding = (l_wind_size.x - m_button_size.x * 4) / 5;  // 4px.

    std::string labels[4];
    labels[0] = "PLAY";
    labels[1] = "PASS";
    labels[2] = "MENU";
    labels[3] = "EXIT";

    m_background.setPosition(0, l_wind_size.y - l_menu_height);
    m_background.setSize(sf::Vector2f(l_wind_size.x, l_menu_height));
    m_background.setFillColor(sf::Color::Black);

    for (int i = 0; i < 4; ++i) {
        sf::Vector2f button_position(
            m_button_padding + m_button_size.x / 2 +
                i * (m_button_size.x + m_button_padding),
            m_button_pos.y
        );
        m_rects[i].setSize(m_button_size);
        m_rects[i].setFillColor(sf::Color(139, 69, 19));
        m_rects[i].setOrigin(m_button_size.x / 2.0f, m_button_size.y / 2.0f);

        m_rects[i].setPosition(button_position);

        m_button_labels[i].setFont(m_font);
        m_button_labels[i].setString(sf::String(labels[i]));
        m_button_labels[i].setCharacterSize(24);

        sf::FloatRect rect = m_button_labels[i].getLocalBounds();
        m_button_labels[i].setOrigin(
            rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f
        );

        m_button_labels[i].setPosition(button_position);
    }
}

bool GameMenuBar::update(sf::Event event, sf::Window *window) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
        mouse_position.x += m_rects[3].getSize().x / 2;
        mouse_position.y += m_rects[3].getSize().y / 2;
        if (mouse_position.x >= m_rects[3].getPosition().x &&
            mouse_position.x <=
                m_rects[3].getPosition().x + m_rects[3].getSize().x &&
            mouse_position.y >= m_rects[3].getPosition().y &&
            mouse_position.y <=
                m_rects[3].getPosition().y + m_rects[3].getSize().y) {
            return true;
        }
    }
    return false;
}

GameMenuBar::~GameMenuBar() = default;

void GameMenuBar::render(sf::RenderWindow *window) {
    window->draw(m_background);
    for (int i = 0; i < 4; ++i) {
        window->draw(m_rects[i]);
        window->draw(m_button_labels[i]);
    }
}
