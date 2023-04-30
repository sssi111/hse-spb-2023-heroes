#include "menu.hpp"

namespace menu_view {
Menu::Menu() : m_window(
          "Menu: Battle of Heroes and Villains",
          sf::Vector2u(1920, 1080)
      ) {
    m_current_page = PageType::Entry;

    m_buttons.resize(10);
    m_captions.resize(1);

    sf::Vector2u window_size = m_window.get_render_window()->getSize();
    sf::Vector2f button_size = sf::Vector2f(200.0f, 60.0f);


    // entry page
    m_captions[0] = Caption(sf::Vector2f(window_size.x / 2, window_size.y / 2 - 3 * button_size.y), button_size,
                            game_view::Fonts::Montserrat, 48, "Battle of Heroes and Villains", PageType::Entry);

    m_buttons[0] = MenuButton(
        sf::Vector2f(window_size.x / 2, window_size.y / 2 - 1.5 * button_size.y), button_size, sf::Color(139, 69, 19),
        game_view::Fonts::Montserrat, 24, "login", PageType::Entry,
        PageType::Login
    );
    m_buttons[1] = MenuButton(
        sf::Vector2f(window_size.x / 2, window_size.y / 2), button_size, sf::Color(139, 69, 19),
        game_view::Fonts::Montserrat, 24, "registration", PageType::Entry,
        PageType::Registration
    );

    m_buttons[3] = MenuButton(
        sf::Vector2f(window_size.x / 2, window_size.y / 2 + 1.5 * button_size.y), button_size, sf::Color(139, 69, 19),
        game_view::Fonts::Montserrat, 24, "exit", PageType::Entry,
        PageType::Exit
    );

    // login page
    m_buttons[4] = MenuButton(
        sf::Vector2f(window_size.x / 2, window_size.y / 2), button_size, sf::Color(139, 69, 19),
        game_view::Fonts::Montserrat, 24, "login", PageType::Login,
        PageType::GameChoose
    );

    m_buttons[5] = MenuButton(
        sf::Vector2f(window_size.x / 2, window_size.y / 2), button_size, sf::Color(139, 69, 19),
        game_view::Fonts::Montserrat, 24, "register", PageType::Registration,
        PageType::GameChoose
    );

    // game choose page
    m_buttons[6] = MenuButton(
        sf::Vector2f(window_size.x / 2, window_size.y / 2 - 1.5 * button_size.y), button_size, sf::Color(139, 69, 19),
        game_view::Fonts::Montserrat, 24, "single player", PageType::GameChoose,
        PageType::Hehe
    );
    m_buttons[7] = MenuButton(
        sf::Vector2f(window_size.x / 2, window_size.y / 2), button_size, sf::Color(139, 69, 19),
        game_view::Fonts::Montserrat, 24, "multi player", PageType::GameChoose,
        PageType::Hehe
    );
    m_buttons[8] = MenuButton(
        sf::Vector2f(window_size.x / 2, window_size.y / 2 + 1.5 * button_size.y), button_size, sf::Color(139, 69, 19),
        game_view::Fonts::Montserrat, 24, "exit", PageType::GameChoose,
        PageType::Exit
    );

    m_buttons[9] = MenuButton(
        sf::Vector2f(window_size.x / 2, window_size.y / 2), button_size, sf::Color(139, 69, 19),
        game_view::Fonts::Montserrat, 48, "the end))))", PageType::Hehe,
        PageType::Hehe
    );


}

void Menu::change_page(PageType next_page) {
    m_current_page = next_page;
    if (m_current_page == PageType::Hehe) {
        m_window.set_is_done();
    }
}

void Menu::render() {
    m_window.begin_draw();
    for (int button = 0; button < m_buttons.size(); button++) {
        if (m_current_page == m_buttons[button].m_current_page) {
            m_buttons[button].draw(m_window.get_render_window());
        }
    }
    for (int caption = 0; caption < m_captions.size(); caption++) {
        if (m_current_page == m_captions[caption].m_current_page) {
            m_captions[caption].draw(m_window.get_render_window());
        }
    }
    m_window.end_draw();
}

game_view::Window *Menu::get_window()  {
    return &m_window;
}

void Menu::update() {
    sf::Event event{};
    while (m_window.get_render_window()->pollEvent(event)) {
        for (int button = 0; button < m_buttons.size(); button++) {
            if (m_current_page == m_buttons[button].m_current_page) {
                if (m_buttons[button].update(event, this, &m_window)) {
                    break;
                }
            }
        }
    }
}

MenuButton::MenuButton(
    sf::Vector2f position,
    sf::Vector2f size,
    sf::Color color,
    game_view::Fonts font,
    unsigned int character_size,
    const std::string &label,
    PageType current_page,
    PageType next_page
) {
    m_rect.setSize(size);
    m_rect.setFillColor(color);
    m_rect.setOrigin(size.x / 2.0f, size.y / 2.0f);
    m_rect.setPosition(position);

    m_button = game_view::Button(position, size);

    m_current_page = current_page;
    m_next_page = next_page;

    m_label.setFont(game_view::resource_manager()->load_font(font));
    m_label.setString(sf::String(label));
    m_label.setCharacterSize(character_size);

    sf::FloatRect rect = m_label.getLocalBounds();
    m_label.setOrigin(
        rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f
    );

    m_label.setPosition(position);
}

bool MenuButton::update(sf::Event event, Menu *menu, game_view::Window *window) {
    if (m_button.event_processing(event, window->get_render_window())) {
        //EventManager::update_game_menu(m_button_location, window);
        std::cout << "Pressed\n";
        menu->change_page(m_next_page);
        return true;
    }
    return false;
}

void MenuButton::draw(sf::RenderWindow *window) {
    window->draw(m_rect);
    window->draw(m_label);
}

Caption::Caption(
    sf::Vector2f position,
    sf::Vector2f size,
    game_view::Fonts font,
    unsigned int character_size,
    std::string text,
    PageType current_page
) {
    m_rect.setSize(size);
    m_rect.setFillColor(sf::Color::Black);
    m_rect.setOrigin(size.x / 2.0f, size.y / 2.0f);
    m_rect.setPosition(position);

    m_current_page = current_page;

    m_label.setFont(game_view::resource_manager()->load_font(font));
    m_label.setString(sf::String(text));
    m_label.setFillColor(sf::Color::White);
    m_label.setCharacterSize(character_size);

    sf::FloatRect rect = m_label.getLocalBounds();
    m_label.setOrigin(
        rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f
    );

    m_label.setPosition(position);
}

void Caption::draw(sf::RenderWindow *window) const {
    window->draw(m_rect);
    window->draw(m_label);
}
}// namespace menu_view