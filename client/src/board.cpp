#include "board.hpp"
#include "resource_manager.hpp"

Board::Board(sf::Vector2i window_size) {
    m_cell_amount = 10;
    m_window_size = window_size;
    m_boarder_size.x = m_window_size.x * 0.07;
    m_boarder_size.y = m_window_size.y * 0.07;
    m_cell_size.x = (m_window_size.x - 2 * m_boarder_size.x) / m_cell_amount;
    m_cell_size.y = (m_window_size.y - m_boarder_size.y) / m_cell_amount;
    m_board.resize(m_cell_amount, std::vector<Cell>(m_cell_amount));
    for (int row = 0; row < m_cell_amount; row++) {
        for (int column = 0; column < m_cell_amount; column++) {
            m_board[row][column].set_type(
                CellTextures::Default, m_cell_size.x, m_cell_size.y
            );
            m_board[row][column].get_cell()->setPosition(
                m_boarder_size.x + m_cell_size.x / 2 + m_cell_size.x * column,
                m_boarder_size.y + m_cell_size.y / 2 + m_cell_size.y * row
            );
            m_board[row][column].get_cell()->setOrigin(
                m_cell_size.x / 2, m_cell_size.y / 2
            );
            m_board[row][column].get_label()->setFont(
                resource_manager()->load_font(Fonts::Montserrat)
            );
            m_board[row][column].get_label()->setString(
                m_board[row][column].get_name()
            );
            m_board[row][column].get_label()->setCharacterSize(24);
            sf::FloatRect rect =
                m_board[row][column].get_label()->getLocalBounds();
            sf::FloatRect rect1 =
                m_board[row][column].get_cell()->getGlobalBounds();
            m_board[row][column].get_label()->setPosition(
                rect1.left + rect.width / 2.0f, rect1.top + rect.height / 2.0f
            );
            m_board[row][column].get_label()->setOrigin(
                rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f
            );
            if (column == 0) {
                m_board[row][column].set_unit();
                m_board[row][column].get_unit()->set_type(UnitTextures::Default
                );
                m_board[row][column].get_unit()->set_position(
                    m_boarder_size.x + m_cell_size.x / 2 +
                        m_cell_size.x * column,
                    m_boarder_size.y + m_cell_size.y / 2 + m_cell_size.y * row
                );
                m_board[row][column].get_unit()->set_origin(
                    m_cell_size.x / 2, m_cell_size.y / 2
                );
            }
        }
    }
}

void Board::render(sf::RenderWindow *window) {
    for (auto &row : m_board) {
        for (auto &cell : row) {
            cell.draw(window);
            if (cell.get_is_have_unit()) {
                window->draw(*cell.get_unit()->get_unit());
            }
        }
    }
}
