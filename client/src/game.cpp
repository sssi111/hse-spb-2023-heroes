#include "game.hpp"
#include "board.hpp"

namespace game_view {
Game::Game()
    : m_window("Battle of Heroes and Villains", sf::Vector2u(1920, 1080)),
      m_game_menu_bar(sf::Vector2f(1920, 1080), 100),
      m_board(sf::Vector2i(1920, 980))  // '- 100' is subtraction of menu_height
{
    m_background.setTexture(game_view::resource_manager()->load_cell_texture(
        game_view::CellType::Default
    ));
    m_background.setPosition(0, 0);
}

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
    m_window.get_render_window()->clear(sf::Color(164, 176, 126));
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