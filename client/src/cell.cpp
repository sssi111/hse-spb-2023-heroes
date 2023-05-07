#include "cell.hpp"
#include <string>
#include "client.hpp"
#include "event_manager.hpp"

namespace game_interface {
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
    m_cell_size = size;
    m_cell.setTexture(resource_manager()->load_cell_texture(m_cell_type));
    m_cell.scale(
        size.x / m_cell.getTexture()->getSize().x,
        size.y / m_cell.getTexture()->getSize().y
    );
    m_cell.setPosition(position);
    m_cell.setOrigin(size.x / 2, size.y / 2);

    m_button = interface::Button(position, size);
    m_strength = strength;
    m_unit = unit;
}

bool Cell::is_have_unit() const {
    return m_unit != nullptr;
}

void Cell::set_unit(Unit *unit) {
    m_unit = unit;
    if (unit == nullptr) {
        m_cell.setTexture(
            resource_manager()->load_cell_texture(CellType::Default)
        );
    } else if (!m_is_available_for_moving && m_unit->get_hero_id() != get_client_state()->m_user.user().id()) {
        m_cell.setTexture(resource_manager()->load_cell_texture(CellType::Enemy)
        );
    }
}

void Cell::add_selection() {
    m_is_available_for_moving = true;
    if (is_have_unit() &&
        m_unit->get_hero_id() != get_client_state()->m_user.user().id()) {
        m_cell.setTexture(resource_manager()->load_cell_texture(CellType::Attack
        ));
    } else {
        m_cell.setTexture(
            resource_manager()->load_cell_texture(CellType::Selected)
        );
    }
}

void Cell::remove_selection() {
    m_is_available_for_moving = false;
    if (is_have_unit() &&
        m_unit->get_hero_id() != get_client_state()->m_user.user().id()) {
        m_cell.setTexture(resource_manager()->load_cell_texture(CellType::Enemy)
        );
    } else {
        m_cell.setTexture(
            resource_manager()->load_cell_texture(CellType::Default)
        );
    }
}

void Cell::update_cell(const namespace_proto::Cell &cell) {
    m_strength = cell.durability();

    m_unit = nullptr;

    m_label.setFont(resource_manager()->load_font(interface::Fonts::CaptionFont)
    );
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

    if (is_have_unit()) {
        if (m_unit->get_hero_id() != get_client_state()->m_user.user().id()) {
            m_cell.setTexture(
                resource_manager()->load_cell_texture(CellType::Enemy)
            );
        } else if (!m_is_available_for_moving) {
            m_cell.setTexture(
                resource_manager()->load_cell_texture(CellType::Default)
            );
        }
    }
}

void Cell::handling_event(
    Unit **selected_unit,
    Board *board,
    sf::Event event,
    sf::Window *window
) {
    auto result = m_button.handling_event(event, window);
    if (result == CellEventType::FirstPress) {
        if (is_have_unit() &&
            m_unit->get_hero_id() == get_client_state()->m_user.user().id()) {
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
        } else if (*selected_unit && m_is_available_for_moving) {
            EventManager::update_cell(
                CellEventType::Move, selected_unit, &m_unit, m_coords, board
            );
        }
    }
    if (is_have_unit() &&
        m_unit->get_hero_id() == get_client_state()->m_user.user().id()) {
        m_unit->update_statistic(result, window);
    }
}

void Cell::render(sf::RenderWindow *window) {
    window->draw(m_cell);
    window->draw(m_label);
}

[[nodiscard]] Unit *Cell::get_unit() {
    return m_unit;
}

CellEventType Cell::is_mouse_target(sf::Window *window) {
    sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
    auto cell_position = m_cell.getPosition();
    mouse_position.x += m_cell_size.x / 2;
    mouse_position.y += m_cell_size.y / 2;
    mouse_position.x -= cell_position.x;
    mouse_position.y -= cell_position.y;
    if (mouse_position.x >= 0 && mouse_position.x <= m_cell_size.x &&
        mouse_position.y >= 0 && mouse_position.y <= m_cell_size.y) {
        return CellEventType::Targeting;
    }
    return CellEventType::Nothing;
}

namespace_proto::Cell reverse_cell(namespace_proto::Cell cell) {
    cell.set_column(9 - cell.column());
    return cell;
}
}  // namespace game_interface