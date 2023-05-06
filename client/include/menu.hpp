#ifndef BATTLE_OF_HEROES_HEROES_MENU_HPP
#define BATTLE_OF_HEROES_HEROES_MENU_HPP

#include <vector>
#include "caption.hpp"
#include "enum_classes_fwd.hpp"
#include "menu_button.hpp"
#include "textbox.hpp"
#include "window.hpp"

namespace menu_view {

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
        const std::string &tittle,
        PageType current_page,
        PageType next_page,
        sf::Color font_color
    );

    PageType get_current_page() const;
    PageType get_next_page() const;
    void update_tittle(std::string new_tittle);
    bool update(sf::Event event, game_view::Window *window);
    void draw(sf::RenderWindow *window);

private:
    sf::RectangleShape m_table;
    sf::Text m_data;
    game_view::Button m_button;
    PageType m_current_page;
    PageType m_next_page;
};

class Menu {
public:
    Menu();

    game_view::Window *get_window();
    void change_page(PageType new_page);
    void print_error();
    void render();
    void update();

private:
    game_view::Window m_window;
    std::vector<MenuButton> m_buttons;
    std::vector<Caption> m_captions;
    sf::Sprite m_background;
    PageType m_current_page;
    TextBox m_signup_login;
    TextBox m_signup_password;
    MenuButton m_show_signup_password;
    Caption m_signup_error;
    TextBox m_registration_login;
    TextBox m_registration_password;
    TextBox m_registration_password_checker;
    MenuButton m_show_registration_password;
    Caption m_registration_error;
};
}  // namespace menu_view

#endif  // BATTLE_OF_HEROES_HEROES_MENU_HPP
