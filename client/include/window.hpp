#ifndef BATTLE_OF_HEROES_WINDOW_HPP
#define BATTLE_OF_HEROES_WINDOW_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <utility>
#include "event_manager_fwd.hpp"

class Window {
public:
    Window();
    Window(std::string title, const sf::Vector2u &size);
    ~Window();

    void begin_draw();
    void end_draw();

    void update(sf::Event event);

    bool is_done() const;
    bool is_fullscreen() const;

    void toggle_fullscreen();

    void draw(sf::Drawable &l_drawable);

    sf::RenderWindow *get_render_window();

    friend EventManager;

private:
    void create();
    void setup(std::string title, sf::Vector2u size);
    void destroy();

    sf::RenderWindow m_window;
    sf::Vector2u m_window_size;
    std::string m_window_title;
    bool m_is_done{};
    bool m_is_fullscreen{};
};

#endif  // BATTLE_OF_HEROES_WINDOW_HPP
