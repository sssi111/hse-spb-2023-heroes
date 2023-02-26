#include "game.hpp"
#include "board.hpp"

Game::Game()
    : m_window("Battle of Heroes and Villains", sf::Vector2u(1920, 1080)),
      m_board(sf::Vector2u(1920, 1080)) {
}

Game::~Game() {
}

void Game::update() {
    m_window.update();
}

void Game::render() {
    m_window.begin_draw();
    m_board.render(*m_window.get_render_window());
    m_window.end_draw();
}

Window *Game::get_window() {
    return &m_window;
}
