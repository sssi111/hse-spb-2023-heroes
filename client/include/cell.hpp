#ifndef BATTLE_OF_HEROES_CELL_HPP
#define BATTLE_OF_HEROES_CELL_HPP

#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "enum_classes_fwd.hpp"
#include "unit.hpp"

namespace game_view {
class Board;

class Cell {
public:
    Cell() = default;
    explicit Cell(
        Coords coords,
        CellType type,
        sf::Vector2f position,
        sf::Vector2f size,
        int strength = 0,
        Unit *unit = nullptr
    );

    bool is_have_unit() const;

    void set_unit(Unit *unit);
    [[nodiscard]] Unit *get_unit();
    void add_selection();
    void remove_selection();

    void event_processing(
        Unit **selected_unit,
        Board *board,
        sf::Event event,
        sf::Window *window
    );

    CellEventType targetting(sf::Window *window);

    void update_cell(const namespace_proto::Cell &cell);


    void draw(sf::RenderWindow *window);

private:
    sf::Sprite m_cell;
    Coords m_coords;
    CellType m_cell_type{CellType::Default};
    int m_strength{};
    bool m_is_available_for_moving{};

    Unit *m_unit{};

    Button m_button;
    sf::Text m_label;
};

namespace_proto::Cell reverse_cell(namespace_proto::Cell cell);
}  // namespace game_view

#endif  // BATTLE_OF_HEROES_CELL_HPP
