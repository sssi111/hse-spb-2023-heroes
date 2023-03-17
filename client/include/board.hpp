#ifndef BATTLE_OF_HEROES_BOARD_HPP
#define BATTLE_OF_HEROES_BOARD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "cell.hpp"
#include "client.hpp"
#include "unit.hpp"

class Board {
public:
    explicit Board(sf::Vector2i window_size);
    ~Board() = default;

    [[nodiscard]] sf::Vector2f get_cell_size() const;
    [[nodiscard]] sf::Vector2f get_cell_position(Coords coords) const;

    void move_unit(Unit **unit, Coords new_position);
    void decrease_cell_strength(Coords position);
    void update_board(const namespace_proto::GameState &game_state);

    void update(sf::Event event, sf::Window *window);
    void render(sf::RenderWindow *window);

private:
    std::vector<std::vector<Cell>> m_board;
    std::vector<Unit> m_units;

    Unit *selected_unit;

    sf::Vector2i m_window_size;
    sf::Vector2i m_cell_size;
    sf::Vector2i m_boarder_size;
    int m_cell_amount;
};

#endif  // BATTLE_OF_HEROES_BOARD_HPP
