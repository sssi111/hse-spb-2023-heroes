#ifndef BATTLE_OF_HEROES_HEROES_MENU_HPP
#define BATTLE_OF_HEROES_HEROES_MENU_HPP

#include "enum_classes_fwd.hpp"
#include "menu_button.hpp"
#include "window.hpp"
#include <vector>
#include "textbox.hpp"

namespace menu_view {
class Menu;

class MenuButton {
public:
    MenuButton() = default;
    ~MenuButton() = default;

    MenuButton(
        sf::Vector2f position,
        sf::Vector2f size,
        sf::Color color,
        game_view::Fonts font,
        unsigned character_size,
        const std::string &label,
        PageType current_page,
        PageType next_page
    );

    bool update(sf::Event event, Menu *menu, game_view::Window *window);

    void draw(sf::RenderWindow *window);
    friend Menu;

private:
    sf::RectangleShape m_rect;
    sf::Text m_label;
    game_view::Button m_button;
    PageType m_current_page;
    PageType m_next_page;
};

class Caption {
public:
    Caption() = default;
    ~Caption() = default;

    Caption(
        sf::Vector2f position,
        sf::Vector2f size,
        game_view::Fonts font,
        unsigned character_size,
        std::string text,
        PageType m_current_page
    );

    void draw(sf::RenderWindow *window) const;

    void set_text(std::string text);

    friend Menu;

private:
    sf::RectangleShape m_rect;
    sf::Text m_label;
    PageType m_current_page;
};

class Menu {
public:
    Menu();

    void change_page(PageType new_page);

    game_view::Window *get_window();

    void render();

    void update();

    void print_error();

private:
    game_view::Window m_window;
    std::vector<MenuButton> m_buttons;
    std::vector<Caption> m_captions;
    sf::Sprite m_background;
    PageType m_current_page;
    TextBox m_signup_login;
    TextBox m_signup_password;
    TextBox m_registration_login;
    TextBox m_registration_password;
    TextBox m_registration_password_checker;
    Caption m_signup_error;
    Caption m_registration_error;
};
}

#endif  // HSE_SPB_2023_HEROES_MENU_HPP
