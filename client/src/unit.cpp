#include "unit.hpp"

sf::Sprite *Unit::get_unit() {
    return &m_unit;
}

void Unit::set_type(UnitTextures type) {
    m_type = type;
    m_unit.setTexture(resource_manager()->load_unit_texture(m_type));
}

void Unit::set_position(int pos_x, int pos_y) {
    m_unit.setPosition(pos_x, pos_y);
}

void Unit::set_origin(int pos_x, int pos_y) {
    m_unit.setOrigin(pos_x, pos_y);
}
