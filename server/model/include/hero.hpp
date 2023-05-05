#ifndef MODEL_HERO_HPP
#define MODEL_HERO_HPP

#include "spell_list.hpp"

namespace game_model {
class hero {
private:
    int m_id;
    std::vector<spell> m_spells;

public:
    explicit hero(int id, const std::vector<int> &spells_id) : m_id(id) {
        for (int spell_id : spells_id) {
            m_spells.push_back(const_game_info::SPELL_LIST[spell_id]);
        }
    }

    [[nodiscard]] int get_id() const;

    [[nodiscard]] const std::vector<spell> get_spells() const;
};
}  // namespace game_model

#endif
