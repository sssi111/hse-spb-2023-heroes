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
    m_units.resize(10);
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
            if (column == 0) {
                m_units[row] = Unit(
                    UnitType::Mushroom,
                    sf::Vector2f(
                        m_boarder_size.x + m_cell_size.x / 2 +
                            m_cell_size.x * column,
                        m_boarder_size.y + m_cell_size.y / 2 +
                            m_cell_size.y * row
                    ),
                    sf::Vector2f(m_cell_size), Coords(row, column)
                );
                m_board[row][column].set_unit(&m_units[row]);
            }
        }
    }
}

void Board::move_unit(Unit **unit, Coords new_position) {
    Coords prev_position = (*unit)->get_coords();
    m_board[new_position.get_row()][new_position.get_column()].set_unit(*unit);
    m_board[prev_position.get_row()][prev_position.get_column()].set_unit(
        nullptr
    );
    (*unit)->set_coords(
        new_position,
        sf::Vector2f(
            m_boarder_size.x + m_cell_size.x / 2 +
                m_cell_size.x * new_position.get_column(),
            m_boarder_size.y + m_cell_size.y / 2 +
                m_cell_size.y * new_position.get_row()
        ),
        sf::Vector2f(m_cell_size)
    );
}

void Board::decrease_cell_strength(Coords position) {
    m_board[position.get_row()][position.get_column()].decrease_strength();
}

void Board::update(sf::Event event, sf::Window *window) {
    int row =
        (sf::Mouse::getPosition(*window).y - m_boarder_size.y) / m_cell_size.y;
    int column =
        (sf::Mouse::getPosition(*window).x - m_boarder_size.x) / m_cell_size.x;
    if (column >= 0 && row >= 0 && row < m_cell_amount &&
        column < m_cell_amount) {
        m_board[row][column].update(&selected_unit, this, event, window);
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
        (game_state.second_user() == get_client_state()->user_.user_id());
    for (int cell_index = 0; cell_index < 100; cell_index++) {
        const namespace_proto::Cell &server_cell =
            game_state.game_cells(cell_index);
        int row = server_cell.row();
        int column = server_cell.column();
        if (is_second) {
            column = 9 - column;
        }
        Cell *client_cell = &m_board[row][column];
        if (server_cell.unit().IsInitialized()) {
            int unit_id = server_cell.unit().id_unit();
            // update unit
            // m_units[unit_id].set_coords();
        }
    }
}
