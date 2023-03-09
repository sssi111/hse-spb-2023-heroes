#include "board.hpp"
#include "resource_manager.hpp"

Board::Board(sf::Vector2i window_size) {
    m_cell_amount = 10;
    m_window_size = window_size;
    m_boarder_size.x = static_cast<int>(m_window_size.x * 0.07);
    m_boarder_size.y = static_cast<int>(m_window_size.y * 0.07);
    m_cell_size.x = (m_window_size.x - 2 * m_boarder_size.x) / m_cell_amount;
    m_cell_size.y = (m_window_size.y - m_boarder_size.y) / m_cell_amount;
    m_board.resize(m_cell_amount, std::vector<Cell>(m_cell_amount));
    for (int row = 0; row < m_cell_amount; row++) {
        for (int column = 0; column < m_cell_amount; column++) {
            m_board[row][column] = Cell(
                Coords(row, column), CellType::Default,
                sf::Vector2f(
                    m_boarder_size.x + m_cell_size.x / 2 +
                        m_cell_size.x * column,
                    m_boarder_size.y + m_cell_size.y / 2 + m_cell_size.y * row
                ),
                sf::Vector2f(m_cell_size)
            );
            if (column == 0) {
                m_board[row][column].set_unit(
                    UnitType::Mushroom,
                    sf::Vector2f(
                        m_boarder_size.x + m_cell_size.x / 2 +
                            m_cell_size.x * column,
                        m_boarder_size.y + m_cell_size.y / 2 +
                            m_cell_size.y * row
                    ),
                    sf::Vector2f(m_cell_size)
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
                cell.draw(window);
            }
        }
    }
}

void Board::update(sf::Event event, sf::Window *window) {
    int row =
        (sf::Mouse::getPosition(*window).y - m_boarder_size.y) / m_cell_size.y;
    int column =
        (sf::Mouse::getPosition(*window).x - m_boarder_size.x) / m_cell_size.x;
    if (column >= 0 && row >= 0 && row < m_cell_amount &&
        column < m_cell_amount) {
        m_board[row][column].update(event, window);
    }
}
