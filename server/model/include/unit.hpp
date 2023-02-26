#ifndef MODEL_UNIT_HPP
#define MODEL_UNIT_HPP

namespace game_model {

struct Unit {
    enum class Movement_type = {walking, flying};

private:
    int m_health;
    int m_damage;
    int m_attack_range;
    int m_movement_range;
    int m_x;
    int m_y;
    int m_player_index;
    int m_unit_index;
    Movement_type m_movement_type;
};

}  // namespace game_model

#endif  // MODEL_UNIT_HPP
