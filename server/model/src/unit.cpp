#include "unit.hpp"

namespace game_model {
int Unit::get_movement_range() {
    return m_movement_range();
}
}