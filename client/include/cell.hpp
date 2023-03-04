#ifndef BATTLE_OF_HEROES_CELL_HPP
#define BATTLE_OF_HEROES_CELL_HPP

#include <SFML/Graphics.hpp>
#include "enum_classes_fwd.hpp"
#include "unit.hpp"

class Cell {
public:
    Cell()
        : m_is_have_unit(false),
          m_type(CellTextures::Default),
          m_cell_strength(10),
          m_name(std::to_string(m_cell_strength)){};
    ~Cell() = default;

    sf::Sprite *get_cell();
    Unit *get_unit();
    sf::Text *get_label();
    bool get_is_have_unit() const;
    const std::string &get_name();

    void set_unit();
    void set_type(CellTextures type, int width, int height);

    void draw(sf::RenderWindow *window);

private:
    sf::Sprite m_cell;

private:
    Unit m_unit;
    sf::Text m_label;

    CellTextures m_type;
    bool m_is_have_unit;
    int m_cell_strength{};
    std::string m_name;
};

#endif  // BATTLE_OF_HEROES_CELL_HPP
