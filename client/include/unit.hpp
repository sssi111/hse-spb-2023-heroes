#ifndef BATTLE_OF_HEROES_UNIT_HPP
#define BATTLE_OF_HEROES_UNIT_HPP

#include <SFML/Graphics.hpp>
#include "resource_manager.hpp"

class Unit {
public:
    Unit()
        : m_type(UnitType::Mushroom),
          m_unit(resource_manager()->load_unit_texture(UnitType::Mushroom)),
          m_squad(10) {
    }

    explicit Unit(UnitType unit_type, sf::Vector2f position, sf::Vector2f size);

    ~Unit() = default;

    void draw(sf::RenderWindow *window);

private:
    sf::Sprite m_unit;
    UnitType m_type;
    sf::RectangleShape m_table;
    sf::Text m_label;
    int m_squad;
};

#endif  // BATTLE_OF_HEROES_UNIT_HPP
