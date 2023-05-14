#include "spell.hpp"
#include <utility>

namespace game_model {
spell::spell(
    int id,
    type spell_type,
    std::string name,
    std::string description,
    int mana_cost,
    std::function<void(cell &)> spell_cell_logic,
    std::function<void(unit &)> spell_unit_logic,
    std::function<bool(const cell &, int)> select_cell_logic,
    std::function<bool(const unit &)> select_unit_logic
)
    : m_id(id),
      m_type(spell_type),
      m_name(std::move(name)),
      m_description(std::move(description)),
      m_mana_cost(mana_cost),
      m_spell_cell_logic(std::move(spell_cell_logic)),
      m_spell_unit_logic(std::move(spell_unit_logic)),
      m_select_cell_logic(std::move(select_cell_logic)),
      m_select_unit_logic(std::move(select_unit_logic)) {
}

void spell::operator()(cell &current_cell) const {
    m_spell_cell_logic(current_cell);
}

void spell::operator()(unit &current_unit) const {
    m_spell_unit_logic(current_unit);
}

bool spell::is_selectable(const cell &current_cell, int player_id) const {
    return m_select_cell_logic(current_cell, player_id);
}

bool spell::is_selectable(const unit &current_unit) const {
    return m_select_unit_logic(current_unit);
}

int spell::get_id() const {
    return m_id;
}

int spell::get_mana_cost() const {
    return m_mana_cost;
}

std::string spell::get_name() const {
    return m_name;
}

std::string spell::get_description() const {
    return m_description;
}

spell::type spell::get_type() const {
    return m_type;
}

}  // namespace game_model
