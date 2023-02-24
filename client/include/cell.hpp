#ifndef BATTLE_OF_HEROES_CELL_HPP
#define BATTLE_OF_HEROES_CELL_HPP

#include <SFML/Graphics.hpp>

struct Cell {
    Cell();

    sf::Sprite *get_cell();

    void set_texture(const sf::Texture &texture);

private:
    sf::Sprite m_cell;
};

#endif  // BATTLE_OF_HEROES_CELL_HPP
