#include "unit.hpp"

// plug
Unit::Unit(
    UnitType unit_type,
    sf::Vector2f position,
    sf::Vector2f size,
    Coords coords,
    int id_unit
) {
    m_type = unit_type;
    m_coords = coords;
    m_amount_of_units = 10;
    m_health = 10;
    m_unit_id = id_unit;
    m_hero_id = 0;

    m_unit.setTexture(resource_manager()->load_unit_texture(m_type));
    m_unit.scale(
        size.y / m_unit.getTexture()->getSize().y,
        size.y / m_unit.getTexture()->getSize().y
    );
    m_unit.setPosition(position);
    m_unit.setOrigin(size.x / 2, size.y / 2);

    m_table.setSize(sf::Vector2f(size.x / 4, size.y / 4));
    m_table.setFillColor(sf::Color(139, 69, 19));
    m_table.setOrigin(size.x / 2.0f, size.y / 2.0f);
    m_table.setPosition(
        sf::Vector2f(position.x + 3 * size.x / 4, position.y + 3 * size.y / 4)
    );

    m_label.setFont(resource_manager()->load_font(Fonts::Montserrat));
    m_label.setString(sf::String(std::to_string(m_amount_of_units)));
    m_label.setCharacterSize(24);

    sf::FloatRect rect = m_label.getLocalBounds();
    m_label.setOrigin(rect.left + size.x / 2.0f, rect.top + size.y / 2.0f);

    m_label.setPosition(
        sf::Vector2f(position.x + 13 * size.x / 16, position.y + 3 * size.y / 4)
    );
}

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

void Unit::draw(sf::RenderWindow *window) {
    window->draw(m_unit);
    window->draw(m_table);
    window->draw(m_label);
}

void Unit::set_selection() {
    m_unit.setTexture(
        resource_manager()->load_unit_texture(UnitType::SelectedMushroom)
    );
}

void Unit::disable_selection() {
    m_unit.setTexture(resource_manager()->load_unit_texture(UnitType::Mushroom)
    );
}

void Unit::update_unit(
    UnitType unit_type,
    Coords new_position,
    sf::Vector2f position,
    sf::Vector2f size,
    int health,
    int amount_of_units,
    int id_unit,
    int id_hero
) {
    if (unit_type == UnitType::Empty) {  // then initialize unit
        m_type = unit_type;
        m_coords = new_position;
        m_health = health;
        m_amount_of_units = amount_of_units;
        m_unit_id = id_unit;
        m_hero_id = id_hero;

        m_unit.setTexture(resource_manager()->load_unit_texture(m_type));
        m_unit.scale(
            size.y / m_unit.getTexture()->getSize().y,
            size.y / m_unit.getTexture()->getSize().y
        );
        m_unit.setPosition(position);
        m_unit.setOrigin(size.x / 2, size.y / 2);

        m_table.setSize(sf::Vector2f(size.x / 4, size.y / 4));
        m_table.setFillColor(sf::Color(139, 69, 19));
        m_table.setOrigin(size.x / 2.0f, size.y / 2.0f);
        m_table.setPosition(sf::Vector2f(
            position.x + 3 * size.x / 4, position.y + 3 * size.y / 4
        ));

        m_label.setFont(resource_manager()->load_font(Fonts::Montserrat));
        m_label.setString(sf::String(std::to_string(m_amount_of_units)));
        m_label.setCharacterSize(24);

        sf::FloatRect rect = m_label.getLocalBounds();
        m_label.setOrigin(rect.left + size.x / 2.0f, rect.top + size.y / 2.0f);

        m_label.setPosition(sf::Vector2f(
            position.x + 13 * size.x / 16, position.y + 3 * size.y / 4
        ));
    } else {  // then update
        m_coords = new_position;
        m_unit.setPosition(position);
        m_label.setPosition(sf::Vector2f(
            position.x + 13 * size.x / 16, position.y + 3 * size.y / 4
        ));
        m_table.setPosition(sf::Vector2f(
            position.x + 3 * size.x / 4, position.y + 3 * size.y / 4
        ));
    }
}
