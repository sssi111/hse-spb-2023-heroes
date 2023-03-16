#include "cell.hpp"
#include <string>
#include "event_manager.hpp"

Cell::Cell(
    Coords coords,
    CellType type,
    sf::Vector2f position,
    sf::Vector2f size
) {
    m_coords = coords;
    m_type = type;
    m_cell.setTexture(resource_manager()->load_cell_texture(m_type));
    m_cell.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
    m_cell.setPosition(position);
    m_cell.setOrigin(size.x / 2, size.y / 2);

    m_button = Button(position, size);

    m_cell_strength = 10;

    m_unit = nullptr;

    m_label.setFont(resource_manager()->load_font(Fonts::Montserrat));
    m_label.setString(std::to_string(m_cell_strength));
    m_label.setCharacterSize(24);

    sf::FloatRect label_bounds = m_label.getLocalBounds();
    sf::FloatRect cell_bounds = m_cell.getGlobalBounds();
    m_label.setPosition(
        cell_bounds.left + label_bounds.width / 2.0f,
        cell_bounds.top + label_bounds.height / 2.0f
    );
    m_label.setOrigin(
        label_bounds.left + label_bounds.width / 2.0f,
        label_bounds.top + label_bounds.height / 2.0f
    );
}

bool Cell::is_have_unit() const {
    return m_unit != nullptr;
}

void Cell::set_unit(Unit *unit) {
    m_unit = unit;
}

void Cell::draw(sf::RenderWindow *window) {
    window->draw(m_cell);
    if (is_have_unit()) {
        m_unit->draw(window);
    }
    window->draw(m_label);
}

void Cell::update(
    Unit **selected_unit,
    Board *board,
    sf::Event event,
    sf::Window *window
) {
    if (m_button.update(event, window)) {
        if (is_have_unit()) {
            if (*selected_unit != m_unit) {
                EventManager::update_cell(
                    CellEventType::FirstPress, selected_unit, &m_unit
                );
            } else {
                EventManager::update_cell(
                    CellEventType::SecondPress, selected_unit, &m_unit
                );
            }
        } else {
            if (*selected_unit) {
                EventManager::update_cell(
                    CellEventType::Move, selected_unit, &m_unit, m_coords, board
                );
            }
        }
    }
}