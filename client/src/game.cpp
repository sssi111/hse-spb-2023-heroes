#include "game.hpp"
#include "board.hpp"

Game::Game()
    : m_window("Battle of Heroes and Villains", sf::Vector2u(1920, 1080)),
      m_board(sf::Vector2u(1920, 1080), 100), m_menu_height(100),
        m_game_menu_bar(sf::Vector2f(1920, 1080), 100){
}

Game::~Game() {
}

void Game::handle_input() {
    bool is_done = false;
    m_game_menu_bar.handle_input(is_done, *m_window.get_render_window());
    m_window.handle_input(is_done);
}

void Game::update() {
    m_window.update();
}

void Game::render() {
    m_window.begin_draw();
    m_board.render(*m_window.get_render_window());
    m_game_menu_bar.render(*m_window.get_render_window());
    m_window.end_draw();
}

Window *Game::get_window() {
    return &m_window;
}
