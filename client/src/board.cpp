#include "board.hpp"
#include <utility>
#include "resource_manager.hpp"

Board::Board(sf::Vector2i window_size) {
    m_cell_amount = 10;
    m_window_size = window_size;
    m_boarder_size.x = static_cast<int>(m_window_size.x * 0.07);
    m_boarder_size.y = static_cast<int>(m_window_size.y * 0.07);
    m_cell_size.x = (m_window_size.x - 2 * m_boarder_size.x) / m_cell_amount;
    m_cell_size.y = (m_window_size.y - m_boarder_size.y) / m_cell_amount;
    m_board.resize(m_cell_amount, std::vector<Cell>(m_cell_amount));
    m_units.resize(20);
    selected_unit = nullptr;
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
        }
    }
}

sf::Vector2f Board::get_cell_position(Coords coords) const {
    return {
        static_cast<float>(
            m_boarder_size.x + m_cell_size.x / 2 +
            m_cell_size.x * coords.get_column()
        ),
        static_cast<float>(
            m_boarder_size.y + m_cell_size.y / 2 +
            m_cell_size.y * coords.get_row()
        )};
}

void Board::event_processing(sf::Event event, sf::Window *window) {
    int row =
        (sf::Mouse::getPosition(*window).y - m_boarder_size.y) / m_cell_size.y;
    int column =
        (sf::Mouse::getPosition(*window).x - m_boarder_size.x) / m_cell_size.x;
    if (column >= 0 && row >= 0 && row < m_cell_amount &&
        column < m_cell_amount) {
        m_board[row][column].event_processing(
            &selected_unit, this, event, window
        );
    }
}

void Board::render(sf::RenderWindow *window) {
    for (auto &row : m_board) {
        for (auto &cell : row) {
            cell.draw(window);
        }
    }
}

void Board::update_board(const namespace_proto::GameState &game_state) {
    bool is_second =
        (game_state.second_user() == get_client_state()->m_user.user_id());
    for (int cell_index = 0; cell_index < 100; cell_index++) {
        const namespace_proto::Cell &server_cell =
            game_state.game_cells(cell_index);
        int row = server_cell.row();
        int column = server_cell.column();
        if (is_second) {
            column = 9 - column;
        }
        m_board[row][column].update_cell(server_cell);
        if (server_cell.unit().IsInitialized()) {
            int unit_id = server_cell.unit().id_unit();
            auto server_unit = game_state.game_cells(cell_index).unit();
            m_units[unit_id].update_unit(
                server_cell, server_unit,
                get_cell_position({server_cell.row(), server_cell.column()}),
                static_cast<sf::Vector2f>(m_cell_size)
            );
            m_board[row][column].set_unit(&m_units[unit_id]);
        }
    }
}

void Board::add_available_for_moving_cells(
    std::vector<std::pair<int, int>> selected_cells
) {
    remove_available_for_moving_cells();
    m_available_for_moving_cells = std::move(selected_cells);
    for (auto [row, column] : m_available_for_moving_cells) {
        m_board[row][column].add_selection();
    }
}

void Board::remove_available_for_moving_cells() {
    for (auto [row, column] : m_available_for_moving_cells) {
        m_board[row][column].remove_selection();
    }
    m_available_for_moving_cells.clear();
}
