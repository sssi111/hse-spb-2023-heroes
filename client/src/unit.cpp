#include "unit.hpp"

Unit::Unit(
    UnitType unit_type,
    sf::Vector2f position,
    sf::Vector2f size,
    Coords coords
) {
    m_type = unit_type;
    m_unit.setTexture(resource_manager()->load_unit_texture(m_type));
    m_unit.scale(
        size.y / m_unit.getTexture()->getSize().y,
        size.y / m_unit.getTexture()->getSize().y
    );
    m_unit.setPosition(position);
    m_unit.setOrigin(size.x / 2, size.y / 2);
    m_squad = 11;

    m_coords = coords;

    m_table.setSize(sf::Vector2f(size.x / 4, size.y / 4));
    m_table.setFillColor(sf::Color(139, 69, 19));
    m_table.setOrigin(size.x / 2.0f, size.y / 2.0f);
    m_table.setPosition(
        sf::Vector2f(position.x + 3 * size.x / 4, position.y + 3 * size.y / 4)
    );

    m_label.setFont(resource_manager()->load_font(Fonts::Montserrat));
    m_label.setString(sf::String(std::to_string(m_squad)));
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
