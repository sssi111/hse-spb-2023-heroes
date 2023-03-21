#include "cell.hpp"
#include <string>
#include "client.hpp"
#include "event_manager.hpp"

namespace game_view {
Cell::Cell(
    Coords coords,
    CellType type,
    sf::Vector2f position,
    sf::Vector2f size,
    int strength,
    Unit *unit
) {
    m_coords = coords;
    m_cell_type = type;
    m_cell.setTexture(resource_manager()->load_cell_texture(m_cell_type));
    m_cell.setTextureRect(
        sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y))
    );
    m_cell.setPosition(position);
    m_cell.setOrigin(size.x / 2, size.y / 2);

    m_button = Button(position, size);
    m_strength = strength;
    m_unit = unit;
}

bool Cell::is_have_unit() const {
    return m_unit != nullptr;
}

void Cell::set_unit(Unit *unit) {
    m_unit = unit;
}

void Cell::add_selection() {
    m_is_available_for_moving = true;
}

void Cell::remove_selection() {
    m_is_available_for_moving = false;
}

void Cell::update_cell(const namespace_proto::Cell &cell) {
    m_strength = cell.strength();

    m_unit = nullptr;

    m_label.setFont(resource_manager()->load_font(Fonts::Montserrat));
    m_label.setString(std::to_string(m_strength));
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

void Cell::event_processing(
    Unit **selected_unit,
    Board *board,
    sf::Event event,
    sf::Window *window
) {
    if (m_button.event_processing(event, window)) {
        if (is_have_unit() &&
            m_unit->get_hero_id() == get_client_state()->m_user.user_id()) {
            if (*selected_unit != m_unit) {
                EventManager::update_cell(
                    CellEventType::FirstPress, selected_unit, &m_unit, m_coords,
                    board
                );
            } else {
                EventManager::update_cell(
                    CellEventType::SecondPress, selected_unit, &m_unit,
                    m_coords, board
                );
            }
        } else if (!is_have_unit()) {
            if (*selected_unit && m_is_available_for_moving) {
                EventManager::update_cell(
                    CellEventType::Move, selected_unit, &m_unit, m_coords, board
                );
            }
        }
    }
}

void Cell::draw(sf::RenderWindow *window) {
    window->draw(m_cell);
    window->draw(m_label);
}
}  // namespace game_view