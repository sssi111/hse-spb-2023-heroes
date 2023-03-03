#ifndef BATTLE_OF_HEROES_CELL_HPP
#define BATTLE_OF_HEROES_CELL_HPP

#include <SFML/Graphics.hpp>
#include "unit.hpp"

struct Cell {
    Cell();

    sf::Sprite *get_cell();

    Unit *get_unit();

    bool *is_have_unit();

    void set_unit();

    void set_texture(const sf::Texture &texture);

private:
    sf::Sprite m_cell;
    Unit m_unit;
    bool m_is_unit;
    int m_capacity_cell;
};

#endif  // BATTLE_OF_HEROES_CELL_HPP
