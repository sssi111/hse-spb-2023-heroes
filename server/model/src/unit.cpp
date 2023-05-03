#include "unit.hpp"
#include <algorithm>

namespace game_model {

[[nodiscard]] int unit::get_type() const {
    return m_type;
}

[[nodiscard]] int unit::get_number() const {
    return m_number;
}

[[nodiscard]] int unit::get_health() const {
    return m_health;
}

int unit::get_movement_range() const {
    return m_movement_range;
}

void unit::decrease_health(int damage) {
    m_health = std::max(0, m_health - damage);
    if (m_health == 0) {
        if (m_number > 0)
            --m_number;
        m_health = m_max_health;
    }
}

int unit::get_damage() const {
    return m_damage * m_number;
}

int unit::get_weight() const {
    return m_weight * m_number;
}

bool unit::is_dead() const {
    return m_number == 0;
}

int unit::get_attack_range() const {
    return m_attack_range;
}
}  // namespace game_model