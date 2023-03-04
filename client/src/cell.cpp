#include "cell.hpp"
#include <string>

sf::Sprite *Cell::get_cell() {
    return &m_cell;
}

Unit *Cell::get_unit() {
    return &m_unit;
}

bool Cell::get_is_have_unit() const {
    return m_is_have_unit;
}

void Cell::set_type(CellTextures type, int width, int height) {
    m_type = type;
    m_cell.setTexture(resource_manager()->load_cell_texture(m_type));
    m_cell.setTextureRect(sf::IntRect(0, 0, width, height));
}

void Cell::set_unit() {
    m_is_have_unit = true;
}

sf::Text *Cell::get_label() {
    return &m_label;
}

void Cell::draw(sf::RenderWindow *window) {
    window->draw(m_cell);
    if (m_is_have_unit) {
        window->draw(*m_unit.get_unit());
    }
    window->draw(m_label);
}

const std::string &Cell::get_name() {
    return m_name;
}