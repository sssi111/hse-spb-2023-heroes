#ifndef MODEL_SPELL_HPP
#define MODEL_SPELL_HPP

#include <functional>
#include <string>
#include "cell.hpp"
#include "unit.hpp"

namespace game_model {
class spell {
public:
    enum class type { CELL, UNIT };

private:
    int m_id;
    type m_type;
    std::string m_name;
    std::string m_description;
    int m_mana_cost;
    std::function<void(cell &)> m_spell_cell_logic;
    std::function<void(unit &)> m_spell_unit_logic;
    std::function<bool(const cell &, int)> m_select_cell_logic;
    std::function<bool(const unit &)> m_select_unit_logic;

public:
    spell(
        int id,
        type spell_type,
        std::string name,
        std::string description,
        int mana_cost,
        std::function<void(cell &)> spell_cell_logic,
        std::function<void(unit &)> spell_unit_logic,
        std::function<bool(const cell &, int)> select_cell_logic,
        std::function<bool(const unit &)> select_unit_logic
    );
    void operator()(cell &current_cell) const;
    void operator()(unit &current_unit) const;
    [[nodiscard]] bool is_selectable(const cell &current_cell, int player_id)
        const;
    [[nodiscard]] bool is_selectable(const unit &current_unit) const;
    [[nodiscard]] int get_id() const;
    [[nodiscard]] int get_mana_cost() const;
    [[nodiscard]] std::string get_name() const;
    [[nodiscard]] std::string get_description() const;
    [[nodiscard]] type get_type() const;
};
}  // namespace game_model

#endif  // MODEL_SPELL_HPP
