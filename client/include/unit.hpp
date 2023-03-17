#ifndef BATTLE_OF_HEROES_UNIT_HPP
#define BATTLE_OF_HEROES_UNIT_HPP

#include <SFML/Graphics.hpp>
#include "coordinates.hpp"
#include "resource_manager.hpp"

class Unit {
public:
    Unit()
        : m_type(UnitType::Empty),
          m_coords({-1, -1}),
          m_amount_of_units(),
          m_unit_id(),
          m_health(),
          m_hero_id() {
    }

    explicit Unit(
        UnitType unit_type,
        sf::Vector2f position,
        sf::Vector2f size,
        Coords coords,
        int id_unit
    );

    ~Unit() = default;

    [[nodiscard]] Coords get_coords() const;
    [[nodiscard]] int get_hero_id() const;

    void
    set_coords(Coords new_position, sf::Vector2f position, sf::Vector2f size);
    void set_selection();
    void disable_selection();
    void update_unit(
        UnitType unit_type,
        Coords new_position,
        sf::Vector2f position,
        sf::Vector2f size,
        int health,
        int amount_of_units,
        int id_unit,
        int id_hero
    );

    void draw(sf::RenderWindow *window);

private:
    UnitType m_type;
    Coords m_coords;
    int m_health;
    int m_amount_of_units;
    int m_unit_id;
    int m_hero_id;

    sf::Sprite m_unit;
    sf::RectangleShape m_table;
    sf::Text m_label;
};

#endif  // BATTLE_OF_HEROES_UNIT_HPP
