#include "window.hpp"
#include <utility>
#include "event_manager.hpp"

Window::Window() {
    setup("Heroes", sf::Vector2u(1920, 1080));
}

Window::Window(std::string title, const sf::Vector2u &size) {
    setup(std::move(title), size);
}

Window::~Window() {
    destroy();
}

void Window::create() {
    auto style = (m_is_fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.create(
        {m_window_size.x, m_window_size.y, 32}, m_window_title, style
    );
}

void Window::setup(std::string title, sf::Vector2<unsigned int> size) {
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

sf::RenderWindow *Window::get_render_window() {
    return &m_window;
}

sf::Vector2u Window::get_size() {
    return m_window_size;
}

void Window::begin_draw() {
    m_window.clear(sf::Color::Black);
}

void Window::end_draw() {
    m_window.display();
}

void Window::draw(sf::Drawable &l_drawable) {
    m_window.draw(l_drawable);
}

void Window::toggle_fullscreen() {
    m_is_fullscreen = !m_is_fullscreen;
    destroy();
    create();
}

bool Window::is_done() const {
    return m_is_done;
}

bool Window::is_fullscreen() const {
    return m_is_fullscreen;
}
