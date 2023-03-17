#ifndef BATTLE_OF_HEROES_CELL_HPP
#define BATTLE_OF_HEROES_CELL_HPP

#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "enum_classes_fwd.hpp"
#include "unit.hpp"

class Board;

class Cell {
public:
    Cell() = default;
    explicit Cell(
        Coords coords,
        CellType type,
        sf::Vector2f position,
        sf::Vector2f size
    );

    bool is_have_unit() const;
    void set_unit(Unit *unit);
    void decrease_strength();

    void update(
        Unit **selected_unit,
        Board *board,
        sf::Event event,
        sf::Window *window
    );
    void draw(sf::RenderWindow *window);

private:
    sf::Sprite m_cell;
    Coords m_coords;
    CellType m_cell_type{CellType::Default};
    int m_strength{};

    Unit *m_unit{};

    Button m_button;
    sf::Text m_label;
};

#endif  // BATTLE_OF_HEROES_CELL_HPP
