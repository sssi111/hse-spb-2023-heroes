#include "cell.hpp"

Cell::Cell() {
}

sf::Sprite *Cell::get_cell() {
    return &m_cell;
}

void Cell::set_texture(const sf::Texture &texture) {
    m_cell.setTexture(texture);
}
