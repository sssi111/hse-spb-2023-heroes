#ifndef MODEL_SPELL_HPP
#define MODEL_SPELL_HPP

#include <functional>
#include <string>
#include "cell.hpp"

namespace game_model {
class spell {
private:
    int m_id;
    std::string m_name;
    std::string m_description;
    int m_mana_cost;
    std::function<void(cell &)> m_spell_logic;
    std::function<bool(const cell &, int)> m_select_logic;

public:
    spell(
        int id,
        std::string name,
        std::string description,
        int mana_cost,
        std::function<void(cell &)> spell_logic,
        std::function<bool(const cell &, int)> select_logic
    );
    void operator()(cell &current_cell) const;
    [[nodiscard]] int get_id() const;
    [[nodiscard]] int get_mana_cost() const;
    [[nodiscard]] std::string get_name() const;
    [[nodiscard]] std::string get_description() const;
};
}  // namespace game_model

#endif  // MODEL_SPELL_HPP
