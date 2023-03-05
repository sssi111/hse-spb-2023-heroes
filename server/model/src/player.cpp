#include "player.hpp"
#include "unit.hpp"

namespace game_model {
int Player::get_id() const {
    return id;
}
Unit &Player::get_unit(int index) const {
    return m_units_list[index];
}
}  // namespace game_model