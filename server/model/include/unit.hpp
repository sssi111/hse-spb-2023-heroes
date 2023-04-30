#ifndef MODEL_UNIT_HPP
#define MODEL_UNIT_HPP

#include <utility>
#include "coordinates.hpp"

namespace game_model {

class unit {
private:
    int m_number{5};
    int m_health{10};
    const int m_max_health{10};
    int m_damage{1};
    int m_attack_range{1};
    int m_movement_range{2};

    void decrease_number();

public:
    unit() = default;

    [[nodiscard]] int get_attack_range() const;
    [[nodiscard]] int get_movement_range() const;
    [[nodiscard]] int get_damage() const;
    [[nodiscard]] bool is_dead() const;
    void decrease_health(int damage);
};

}  // namespace game_model

#endif  // MODEL_UNIT_HPP
