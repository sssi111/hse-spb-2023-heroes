#ifndef BATTLE_OF_HEROES_CELL_HPP
#define BATTLE_OF_HEROES_CELL_HPP

#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "enum_classes_fwd.hpp"
#include "unit.hpp"

class Coords {
public:
    Coords() : m_row(0), m_column(0){};
    Coords(int row, int column) : m_row(row), m_column(column){};

private:
    int m_row;
    int m_column;
};

class Cell {
public:
    Cell() = default;
    explicit Cell(
        Coords coords,
        CellType type,
        sf::Vector2f position,
        sf::Vector2f size
    );

    sf::Sprite *get_unit();
    bool get_is_have_unit() const;

    void set_unit(UnitType unit_type, sf::Vector2f position, sf::Vector2f size);

    void update(sf::Event event, sf::Window *window);
    void draw(sf::RenderWindow *window);

private:
    sf::Sprite m_cell;
    Coords m_coords;
    CellType m_type{CellType::Default};
    int m_cell_strength{};

    Unit m_unit;
    bool m_is_have_unit{};
    bool m_is_unit_active{};

    Button m_button;
    sf::Text m_label;
};

#endif  // BATTLE_OF_HEROES_CELL_HPP
