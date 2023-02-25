#include "board.hpp"
#include <iostream>
#include "config.hpp"

std::string source_dir = RESOURCE_PATH;

Board::Board(sf::Vector2u l_windSize) {
    m_board_size = 10;
    m_window_size = l_windSize;
    m_cell_width = m_window_size.x / m_board_size;
    m_cell_height = m_window_size.y / m_board_size;
    m_board.resize(m_board_size, std::vector<Cell>(m_board_size));
    m_texture.loadFromFile(source_dir + "grass.jpg");
    for (int row = 0; row < m_board_size; row++) {
        for (int column = 0; column < m_board_size; column++) {
            m_board[row][column].set_texture(m_texture);
            m_board[row][column].get_cell()->setOrigin(
                m_cell_width / 2, m_cell_height / 2
            );
            m_board[row][column].get_cell()->setPosition(
                m_cell_width / 2 + m_cell_width * column,
                m_cell_height / 2 + m_cell_height * row
            );
            if (column == 0) {
                m_board[row][column].get_unit()->set_texture(
                    source_dir + "hero.png"
                );
                m_board[row][column].get_unit()->get_unit()->setOrigin(
                    m_cell_width / 2, m_cell_height / 2
                );
                m_board[row][column].get_unit()->get_unit()->setPosition(
                    m_cell_width / 2 + m_cell_width * column,
                    m_cell_height / 2 + m_cell_height * row
                );
                m_board[row][column].set_unit();
            }
        }
    }
}

Board::~Board() {
}

void Board::render(sf::RenderWindow &l_window) {
    for (auto &row : m_board) {
        for (auto &cell : row) {
            l_window.draw(*cell.get_cell());
            if (cell.is_have_unit()) {
                l_window.draw(*cell.get_unit()->get_unit());
            }
        }
    }
}
