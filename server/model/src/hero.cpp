#include "hero.hpp"
namespace game_model{
    int hero::get_id() const {
        return m_id;
    }
    
    const std::vector<spell> hero::get_spells() const {
        return m_spells;
    }
}