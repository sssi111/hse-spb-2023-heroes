#include "spell.hpp"
#include <utility>

namespace game_model {
spell::spell(
    std::string name,
    int mana_cost,
    std::function<void(cell &)> spell_logic,
    std::function<bool(const cell &, int)> select_logic
)
    : m_name(std::move(name)),
      m_mana_cost(mana_cost),
      m_spell_logic(std::move(spell_logic)),
      m_select_logic(std::move(select_logic)) {
}

void spell::operator()(cell &current_cell) const {
    m_spell_logic(current_cell);
}

int spell::get_mana_cost() const {
    return m_mana_cost;
}
}  // namespace game_model