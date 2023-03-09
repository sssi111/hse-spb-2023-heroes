#include "game.hpp"
#include "board.hpp"

void Game::update() {
    sf::Event event{};
    while (m_window.get_render_window()->pollEvent(event)) {
        m_window.update(event);
        m_game_menu_bar.update(event, &m_window);
        m_board.update(event, m_window.get_render_window());
    }
}

void Game::render() {
    m_window.begin_draw();
    m_board.render(m_window.get_render_window());
    m_game_menu_bar.render(m_window.get_render_window());
    m_window.end_draw();
}

Window *Game::get_window() {
    return &m_window;
}
