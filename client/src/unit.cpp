#include "unit.hpp"

namespace game_view {
    Coords Unit::get_coords() const {
        return m_coords;
    }

    int Unit::get_hero_id() const {
        return m_hero_id;
    }

    void Unit::set_coords(
        Coords new_position, sf::Vector2f position, sf::Vector2f size
    ) {
        m_coords = new_position;
        m_unit.setPosition(position);
        m_label.setPosition(sf::Vector2f(
            position.x + 13 * size.x / 16, position.y + 3 * size.y / 4
        ));
        m_table.setPosition(sf::Vector2f(
            position.x + 3 * size.x / 4, position.y + 3 * size.y / 4
        ));
    }

    void Unit::draw(sf::RenderWindow * window) {
        window->draw(m_unit);
        window->draw(m_table);
        window->draw(m_label);
    }

    void Unit::set_selection() {
        m_unit.setTexture(
            resource_manager()->load_unit_texture(UnitType::SelectedMushroom)
        );
    }

    void Unit::disable_selection() {
        m_unit.setTexture(
            resource_manager()->load_unit_texture(UnitType::Mushroom)
        );
    }

    void Unit::update_unit(
        const namespace_proto::Cell &cell, const namespace_proto::Unit &unit,
        sf::Vector2f new_position, sf::Vector2f size
    ) {
        if (static_cast<UnitType>(unit.type_unit()) !=
            UnitType::Empty) {  // then initialize unit
            m_type = static_cast<UnitType>(unit.type_unit());
            m_coords = {cell.row(), cell.column()};
            m_health = unit.sum_of_health();
            m_amount_of_units = unit.amount_unit();
            m_unit_id = unit.id_unit();
            m_hero_id = unit.id_hero();
            is_selected = false;

            m_unit.setTexture(resource_manager()->load_unit_texture(m_type));
            m_unit.scale(
                size.y / m_unit.getTexture()->getSize().y,
                size.y / m_unit.getTexture()->getSize().y
            );
            m_unit.setPosition(new_position);
            m_unit.setOrigin(size.x / 2, size.y / 2);

            m_table.setSize(sf::Vector2f(size.x / 4, size.y / 4));
            m_table.setFillColor(sf::Color(139, 69, 19));
            m_table.setOrigin(size.x / 2.0f, size.y / 2.0f);
            m_table.setPosition(sf::Vector2f(
                new_position.x + 3 * size.x / 4, new_position.y + 3 * size.y / 4
            ));

            m_label.setFont(resource_manager()->load_font(Fonts::Montserrat));
            m_label.setString(sf::String(std::to_string(m_amount_of_units)));
            m_label.setCharacterSize(24);

            sf::FloatRect rect = m_label.getLocalBounds();
            m_label.setOrigin(
                rect.left + size.x / 2.0f, rect.top + size.y / 2.0f
            );

            m_label.setPosition(sf::Vector2f(
                new_position.x + 13 * size.x / 16,
                new_position.y + 3 * size.y / 4
            ));
        } else {  // then event_processing
            is_selected = unit.is_selected();
            m_coords = {cell.row(), cell.column()};
            m_unit.setPosition(new_position);
            m_label.setPosition(sf::Vector2f(
                new_position.x + 13 * size.x / 16,
                new_position.y + 3 * size.y / 4
            ));
            m_table.setPosition(sf::Vector2f(
                new_position.x + 3 * size.x / 4, new_position.y + 3 * size.y / 4
            ));
        }
    }
}