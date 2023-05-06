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
    m_cell.scale(
        size.x / m_cell.getTexture()->getSize().x,
        size.y / m_cell.getTexture()->getSize().y
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
    m_cell.setTexture(resource_manager()->load_cell_texture(CellType::Selected)
    );
}

void Cell::remove_selection() {
    m_is_available_for_moving = false;
    m_cell.setTexture(resource_manager()->load_cell_texture(CellType::Default));
}

void Cell::update_cell(const namespace_proto::Cell &cell) {
    m_strength = cell.durability();

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
    auto result = m_button.event_processing(event, window);
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

void Cell::draw(sf::RenderWindow *window) {
    window->draw(m_cell);
    window->draw(m_label);
}

Unit *Cell::get_unit() {
    return m_unit;
}

CellEventType Cell::targetting(sf::Window *window) {
    sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
    auto cell_bounds = m_cell.getLocalBounds();
    auto cell_position = m_cell.getPosition();
    mouse_position.x += cell_bounds.width / 2;
    mouse_position.y += cell_bounds.height / 2;
    mouse_position.x -= cell_position.x;
    mouse_position.y -= cell_position.y;

//    std::cout << cell_bounds.left<< ' ' <<  cell_bounds.left + cell_bounds.width << " - target left cell\n";
//    std::cout << cell_bounds.top << ' ' <<  cell_bounds.top + cell_bounds.height << " - target top cell\n";
    if (mouse_position.x >= 0 &&
        mouse_position.x <= cell_bounds.width &&
        mouse_position.y >=0 &&
        mouse_position.y <= cell_bounds.height) {
        std::cout << mouse_position.x << ' ' << mouse_position.y << " - target mouse\n";
        return CellEventType::Targeting;
    }
    return CellEventType::Nothing;
}

namespace_proto::Cell reverse_cell(namespace_proto::Cell cell) {
    cell.set_column(9 - cell.column());
    return cell;
}
}  // namespace game_view