#include "game.hpp"
#include "board.hpp"

namespace game_interface {
Game::Game()
    : m_window("Battle of Heroes and Villains", sf::Vector2u(1920, 1080)),
      m_game_menu_bar(sf::Vector2f(1920, 1080), 100),
      m_board(sf::Vector2i(1920, 980)) {
    m_background.setTexture(
        game_interface::resource_manager()->load_cell_texture(
            game_interface::CellType::Default
        )
    );
    m_background.setPosition(0, 0);
}

void Game::update() {
    sf::Event event{};
    while (m_window.get_render_window()->pollEvent(event)) {
        m_window.update(event);
        m_game_menu_bar.update(event, &m_window);
        m_board.handling_event(event, m_window.get_render_window());
    }
}

void Game::render() {
    m_window.begin_draw();
    m_window.get_render_window()->clear(sf::Color(164, 176, 126));
    m_board.render(m_window.get_render_window());
    m_game_menu_bar.render(m_window.get_render_window());
    m_window.end_draw();
}

[[nodiscard]] Window *Game::get_window() {
    return &m_window;
}

[[nodiscard]] Board *Game::get_board() {
    return &m_board;
}

[[nodiscard]] GameMenuBar *Game::get_game_menu_bar() {
    return &m_game_menu_bar;
}

[[nodiscard]] Game *get_game_state() {
    static Game game_state;
    return &game_state;
}

[[nodiscard]] sf::Cursor &get_cursor() {
    static sf::Cursor cursor;
    return cursor;
}
}  // namespace game_interface