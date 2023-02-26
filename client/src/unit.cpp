#include "unit.hpp"

Unit::Unit() {
}

sf::Sprite *Unit::get_unit() {
    return &m_unit;
}

void Unit::set_texture(const std::string texture) {
    m_texture.loadFromFile(texture);
    m_unit.setTexture(m_texture);
}
