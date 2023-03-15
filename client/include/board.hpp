#ifndef BATTLE_OF_HEROES_BOARD_HPP
#define BATTLE_OF_HEROES_BOARD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "cell.hpp"
#include "unit.hpp"

class Board {
public:
    explicit Board(sf::Vector2i window_size);
    ~Board() = default;

    void update(sf::Event event, sf::Window *window);
    void render(sf::RenderWindow *window);

private:
    std::vector<std::vector<Cell>> m_board;

    sf::Vector2i m_window_size;
    sf::Vector2i m_cell_size;
    sf::Vector2i m_boarder_size;
    int m_cell_amount;
};

#endif  // BATTLE_OF_HEROES_BOARD_HPP
