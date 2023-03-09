#include "unit.hpp"

Unit::Unit(UnitType unit_type, sf::Vector2f position, sf::Vector2f size) {
    m_type = unit_type;
    m_unit.setTexture(resource_manager()->load_unit_texture(m_type));
    m_unit.setPosition(position);
    m_unit.setOrigin(size.x / 2, size.y / 2);
    m_squad = 10;
}

sf::Sprite *Unit::get_unit() {
    return &m_unit;
}