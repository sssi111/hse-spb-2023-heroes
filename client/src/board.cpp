#include "board.hpp"

Board::Board(sf::Vector2u l_windSize) {
    m_board_size = 10;
    m_window_size = l_windSize;
    m_cell_wigth = m_window_size.x / m_board_size;
    m_cell_height = m_window_size.y / m_board_size;
    m_board.resize(m_board_size, std::vector<Cell>(m_board_size));
    m_texture.loadFromFile("./content/grass.jpg");
    for (int row = 0; row < m_board_size; row++) {
        for (int column = 0; column < m_board_size; column++) {
            m_board[row][column].set_texture(m_texture);
            m_board[row][column].get_cell()->setOrigin(
                m_cell_wigth / 2, m_cell_height / 2
            );
            m_board[row][column].get_cell()->setPosition(
                m_cell_wigth / 2 + m_cell_wigth * column,
                m_cell_height / 2 + m_cell_height * row
            );
        }
    }
}

Board::~Board() {
}

void Board::render(sf::RenderWindow &l_window) {
    for (auto &row : m_board) {
        for (auto &column : row) {
            l_window.draw(*column.get_cell());
        }
    }
}
