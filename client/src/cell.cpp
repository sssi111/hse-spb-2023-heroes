#include "cell.hpp"

Cell::Cell() {
    m_is_unit = false;
}

sf::Sprite *Cell::get_cell() {
    return &m_cell;
}

Unit *Cell::get_unit() {
    return &m_unit;
}

bool *Cell::is_have_unit() {
    return &m_is_unit;
}

void Cell::set_unit() {
    m_is_unit = true;
}

void Cell::set_texture(const sf::Texture &texture) {
    m_cell.setTexture(texture);
}
