#include "game.hpp"
#include "board.hpp"

Game::Game()
    : m_window("Battle of Heroes and Villains", sf::Vector2u(1920, 1080)),
      m_board(sf::Vector2i(1920, 1080), 100),
      m_game_menu_bar(sf::Vector2f(1920, 1080), 100),
      m_event_manager(&m_window, &m_game_menu_bar) {
}

Game::~Game() = default;

void Game::update() {
    sf::Event event{};
    while (m_window.get_render_window()->pollEvent(event)) {
        m_event_manager.update(event);
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
