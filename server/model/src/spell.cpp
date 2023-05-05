#include "spell.hpp"
#include <utility>

namespace game_model {
spell::spell(
    int id,
    std::string name,
    std::string description,
    int mana_cost,
    std::function<void(cell &)> spell_logic,
    std::function<bool(const cell &, int)> select_logic
)
    : m_id(id),
      m_name(std::move(name)),
      m_description(std::move(description)),
      m_mana_cost(mana_cost),
      m_spell_logic(std::move(spell_logic)),
      m_select_logic(std::move(select_logic)) {
}

void spell::operator()(cell &current_cell) const {
    m_spell_logic(current_cell);
}

bool spell::is_selectable(const cell &current_cell, int player_id) const {
    return m_select_logic(current_cell, player_id);
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

}  // namespace game_model