#ifndef BATTLE_OF_HEROES_UNIT_HPP
#define BATTLE_OF_HEROES_UNIT_HPP

#include <SFML/Graphics.hpp>

struct Unit {
    Unit();

    sf::Sprite *get_unit();

    void set_texture(const std::string texture);

private:
    sf::Sprite m_unit;
    sf::Texture m_texture;
    int m_squad;
};

#endif  // BATTLE_OF_HEROES_UNIT_HPP
