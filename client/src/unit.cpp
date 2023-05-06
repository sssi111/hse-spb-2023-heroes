#include "unit.hpp"

namespace game_interface {
Coords Unit::get_coords() const {
    return m_coords;
}

int Unit::get_hero_id() const {
    return m_hero_id;
}

void Unit::set_coords(
    Coords new_position,
    sf::Vector2f position,
    sf::Vector2f size
) {
    m_coords = new_position;
    m_unit.setPosition(position);
    m_label.setPosition(
        sf::Vector2f(position.x + 13 * size.x / 16, position.y + 3 * size.y / 4)
    );
    m_table.setPosition(
        sf::Vector2f(position.x + 3 * size.x / 4, position.y + 3 * size.y / 4)
    );
}

void Unit::render(sf::RenderWindow *window) {
    window->draw(m_unit);
    window->draw(m_table);
    window->draw(m_label);
    auto mouse_position = sf::Mouse::getPosition(*window);
    m_statistic.render(window);
}

void Unit::set_selection() {
    m_unit.setTexture(resource_manager()->load_selected_unit_texture(m_type));
}

void Unit::disable_selection() {
    m_unit.setTexture(resource_manager()->load_unit_texture(m_type));
}

void Unit::update_characteristics(const namespace_proto::Unit &unit) {
    m_number_of_units = unit.amount_unit();
    m_max_health = unit.sum_of_health();
    m_damage = unit.damage();
    m_attack_range = unit.attack_range();
    m_movement_range = unit.movement_range();
    m_weight = unit.weight();
}

void Unit::update_unit(
    namespace_proto::Cell cell,
    const namespace_proto::Unit &unit,
    sf::Vector2f new_position,
    sf::Vector2f size
) {
    new_position.x += size.x / 4;
    new_position.y += size.y / 4 - 3;
    if (unit.type_unit() != 0) {  // then initialize unit
        if (m_type != static_cast<UnitType>(unit.type_unit())) {
            m_type = static_cast<UnitType>(unit.type_unit());
            m_unit.setTexture(resource_manager()->load_unit_texture(m_type));
            m_unit.scale(
                size.y / m_unit.getTexture()->getSize().y,
                size.y / m_unit.getTexture()->getSize().y
            );
        }
        m_coords = {cell.row(), cell.column()};
        m_amount_of_units = unit.amount_unit();
        m_unit_id = unit.id_unit();
        m_hero_id = unit.id_hero();
        is_selected = false;
        update_characteristics(unit);

        m_unit.setPosition(new_position);
        m_unit.setOrigin(size.x / 2, size.y / 2);

        m_table.setSize(sf::Vector2f(size.x / 4, size.y / 4));
        m_table.setFillColor(sf::Color(139, 69, 19));
        m_table.setOrigin(size.x / 2.0f, size.y / 2.0f);
        m_table.setPosition(sf::Vector2f(
            new_position.x + 3 * size.x / 4, new_position.y + 3 * size.y / 4
        ));

        m_label.setFont(
            resource_manager()->load_font(interface::Fonts::CaptionFont)
        );
        m_label.setString(sf::String(std::to_string(m_amount_of_units)));
        m_label.setCharacterSize(24);

        sf::FloatRect rect = m_label.getLocalBounds();
        m_label.setOrigin(rect.left + size.x / 2.0f, rect.top + size.y / 2.0f);

        m_label.setPosition(sf::Vector2f(
            new_position.x + 13 * size.x / 16, new_position.y + 3 * size.y / 4
        ));

        m_statistic = interface::PopUpWindow(
            new_position, {0, 0}, interface::Fonts::CaptionFont, 20,
            "number of units: 5\nmax health: 10\ndamage: 1\nattack range: "
            "1\nmovement range: 2\nweight: 1"
        );

    } else {  // then handling_event
        update_characteristics(unit);
        is_selected = unit.is_selected();
        m_coords = {cell.row(), cell.column()};
        m_unit.setPosition(new_position);
        m_label.setPosition(sf::Vector2f(
            new_position.x + 13 * size.x / 16, new_position.y + 3 * size.y / 4
        ));
        m_table.setPosition(sf::Vector2f(
            new_position.x + 3 * size.x / 4, new_position.y + 3 * size.y / 4
        ));
    }
}

void Unit::update_statistic(
    CellEventType event_type,
    const sf::Window *window
) {
    m_statistic.update(
        "number of units: 5\n"
        "max health: 10\n"
        "damage: 1\n"
        "attack range: 1\n"
        "movement range: 2\n"
        "weight: 1",
        event_type, window
    );
}
}  // namespace game_interface
