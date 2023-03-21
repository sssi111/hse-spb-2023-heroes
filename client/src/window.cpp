#include "window.hpp"
#include <utility>

namespace game_view {
    Window::Window(std::string title, const sf::Vector2u &size) {
        setup(std::move(title), size);
    }

    Window::~Window() {
        destroy();
    }

    void Window::create() {
        auto style =
            (m_is_fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
        m_window.create(
            {m_window_size.x, m_window_size.y, 32}, m_window_title, style
        );
    }

    void Window::setup(std::string title, sf::Vector2u size) {
        m_window_title = std::move(title);
        m_window_size = size;
        m_is_done = false;
        m_is_fullscreen = false;
        m_window.setFramerateLimit(60);
        create();
    }

    void Window::destroy() {
        m_window.close();
    }

    void Window::update(sf::Event event) {
        if (event.type == sf::Event::Closed) {
            m_is_done = true;
        } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) {
            toggle_fullscreen();
        }
    }

    [[nodiscard]] sf::RenderWindow *Window::get_render_window() {
        return &m_window;
    }

    void Window::begin_draw() {
        m_window.clear(sf::Color::Black);
    }

    void Window::end_draw() {
        m_window.display();
    }

    void Window::draw(sf::Drawable & drawable_object) {
        m_window.draw(drawable_object);
    }

    void Window::toggle_fullscreen() {
        m_is_fullscreen = !m_is_fullscreen;
        destroy();
        create();
    }

    [[nodiscard]] bool Window::is_done() const {
        return m_is_done;
    }

    [[nodiscard]] bool Window::is_fullscreen() const {
        return m_is_fullscreen;
    }

    void Window::set_is_done() {
        m_is_done = true;
    }
}