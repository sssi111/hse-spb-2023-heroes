#include "cell.hpp"
#include <string>
#include "client.hpp"
#include "event_manager.hpp"
#include "game.hpp"

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
    m_cell_frame.setTexture(resource_manager()->load_cell_frame_texture(CellType::Default));
    m_cell_frame.scale(
        size.x / m_cell.getTexture()->getSize().x,
        size.y / m_cell.getTexture()->getSize().y
    );
    m_cell_frame.setPosition(position);

    m_button = interface::Button(
        {position.x + m_cell_size.x / 2, position.y + m_cell_size.y / 2}, size
    );
    m_durability = strength;
    m_unit = unit;
}

bool Cell::is_have_unit() const {
    return m_unit != nullptr;
}

void Cell::update_cell_texture(CellType type) {
    m_cell_frame_type = type;
    if (is_have_unit() &&
        m_unit->get_hero_id() != get_client_state()->m_user.user().id()) {
        m_cell_frame_type = CellType::Enemy;
    }
    if (type == CellType::Selected) {
        if (is_have_unit() &&
            m_unit->get_hero_id() != get_client_state()->m_user.user().id()) {
            m_cell_frame_type = CellType::Attack;
        } else {
            m_cell_frame_type = CellType::Selected;
        }
    }
    int column = m_coords.get_column();
    if (get_client_state()->m_game_state.second_user() ==
        get_client_state()->m_user.user().id()) {
        column = 9 - column;
    }
    m_durability =
        get_client_state()
            ->m_game_state.game_cells(m_coords.get_row() * 10 + column)
            .durability();
    if (m_durability < 10) {
        m_cell_type = CellType::Broken;
    } else {
        m_cell_type = CellType::Default;
    }
    m_cell.setTexture(resource_manager()->load_cell_texture(m_cell_type));
    m_cell_frame.setTexture(resource_manager()->load_cell_frame_texture(m_cell_frame_type));
}

void Cell::set_unit(Unit *unit) {
    m_unit = unit;
    update_cell_texture(CellType::Default);
}

void Cell::add_spelling(int spell_id) {
    m_spell_id = spell_id;
    update_cell_texture(CellType::EnableForSpellbinding);
}

void Cell::remove_spelling() {
    m_spell_id = -1;
    update_cell_texture(CellType::Default);
}

void Cell::update_cell(const namespace_proto::Cell &cell) {
    m_durability = cell.durability();
    m_unit = nullptr;

    m_label.setFont(resource_manager()->load_font(interface::Fonts::CaptionFont)
    );
    m_label.setString(std::to_string(m_durability));
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
        update_cell_texture(CellType::Default);
    }
}

void Cell::handling_event(
    Unit **selected_unit,
    Board *board,
    sf::Event event,
    sf::Window *window
) {
    auto result = m_button.handling_event(event, window);
    if (result == EventType::FirstPress) {
        if (m_cell_type == CellType::EnableForSpellbinding) {
            EventManager::apply_spell(
                m_spell_id, m_coords.get_row(), m_coords.get_column()
            );
            get_game_state()->get_board()->remove_enable_for_spelling_cells();
            get_game_state()->get_game_menu_bar()->set_spells_to_default();
            get_game_state()->get_board()->update_board(
                get_client_state()->m_game_state
            );
        } else if (is_have_unit() &&
            m_unit->get_hero_id() == get_client_state()->m_user.user().id()) {
            if (*selected_unit != m_unit) {
                EventManager::update_cell(
                    EventType::FirstPress, selected_unit, &m_unit, m_coords,
                    board
                );
            } else {
                EventManager::update_cell(
                    EventType::SecondPress, selected_unit, &m_unit, m_coords,
                    board
                );
            }
        } else if (*selected_unit && m_is_available_for_moving) {
            EventManager::update_cell(
                EventType::Move, selected_unit, &m_unit, m_coords, board
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
    window->draw(m_cell_frame);
    window->draw(m_label);
}

[[nodiscard]] Unit *Cell::get_unit() {
    return m_unit;
}

EventType Cell::is_mouse_target(sf::Window *window) {
    sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
    auto cell_position = m_cell.getPosition();
    mouse_position.x -= cell_position.x;
    mouse_position.y -= cell_position.y;
    if (mouse_position.x >= 0 && mouse_position.x <= m_cell_size.x &&
        mouse_position.y >= 0 && mouse_position.y <= m_cell_size.y &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
        return EventType::Targeting;
    }
    return EventType::Nothing;
}

void Cell::add_selection() {
    m_is_available_for_moving = true;
    update_cell_texture(CellType::Selected);
}

void Cell::remove_selection() {
    m_is_available_for_moving = false;
    update_cell_texture(CellType::Default);
}

namespace_proto::Cell reverse_cell(namespace_proto::Cell cell) {
    cell.set_column(9 - cell.column());
    return cell;
}
}  // namespace game_interface