#ifndef BATTLE_OF_HEROES_UNIT_HPP
#define BATTLE_OF_HEROES_UNIT_HPP

#include <SFML/Graphics.hpp>
#include "resource_manager.hpp"

class Unit {
public:
    Unit();

    sf::Sprite *get_unit();

    void set_type(UnitTextures type);
    void set_position(int pos_x, int pos_y);
    void set_origin(int pos_x, int pos_y);

private:
    sf::Sprite m_unit;
    UnitTextures m_type;
    int m_squad;
};

#endif  // BATTLE_OF_HEROES_UNIT_HPP
