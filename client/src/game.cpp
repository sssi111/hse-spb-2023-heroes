#include "game.hpp"
#include "board.hpp"

namespace game_view {
void Game::update() {
    sf::Event event{};
    while (m_window.get_render_window()->pollEvent(event)) {
        m_window.update(event);
        m_game_menu_bar.update(event, &m_window);
        m_board.event_processing(event, m_window.get_render_window());
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

Board *Game::get_board() {
    return &m_board;
}

Game *get_game_state() {
    static Game game_state;
    return &game_state;
}
}  // namespace game_view