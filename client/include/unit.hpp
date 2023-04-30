#ifndef BATTLE_OF_HEROES_UNIT_HPP
#define BATTLE_OF_HEROES_UNIT_HPP

#include <SFML/Graphics.hpp>
#include "client.hpp"
#include "coordinates.hpp"
#include "resource_manager.hpp"

namespace game_view {
class Unit {
public:
    Unit()
        : m_type(UnitType::Empty),
          m_coords({-1, -1}),
          m_amount_of_units(),
          m_unit_id(),
          m_health(),
          m_hero_id(),
          is_selected() {
    }

    ~Unit() = default;

    [[nodiscard]] Coords get_coords() const;
    [[nodiscard]] int get_hero_id() const;

    void
    set_coords(Coords new_position, sf::Vector2f position, sf::Vector2f size);
    void set_selection();
    void disable_selection();
    void update_unit(
        namespace_proto::Cell cell,
        const namespace_proto::Unit &unit,
        sf::Vector2f new_position,
        sf::Vector2f size
    );

    void draw(sf::RenderWindow *window);

private:
    UnitType m_type;
    Coords m_coords;
    int m_health;
    int m_amount_of_units;
    int m_unit_id;
    int m_hero_id;
    bool is_selected;

    sf::Sprite m_unit;
    sf::RectangleShape m_table;
    sf::Text m_label;
};
}  // namespace game_view

#endif  // BATTLE_OF_HEROES_UNIT_HPP
