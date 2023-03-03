#ifndef BATTLE_OF_HEROES_BOARD_HPP
#define BATTLE_OF_HEROES_BOARD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "cell.hpp"
#include "unit.hpp"

struct Board {
    Board(sf::Vector2u l_windSize, unsigned int l_menu_height);
    ~Board();

    void render(sf::RenderWindow &l_window);

private:
    sf::Vector2u m_window_size;
    int m_board_size;
    unsigned int m_cell_width;
    unsigned int m_cell_height;
    std::vector<std::vector<Cell>> m_board;
    sf::Texture m_texture;
};

#endif  // BATTLE_OF_HEROES_BOARD_HPP
