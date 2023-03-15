#ifndef MODEL_UNIT_HPP
#define MODEL_UNIT_HPP

#include <utility>
#include "coordinates.hpp"

namespace game_model {

class unit {
private:
    int m_health{10};
    int m_damage{1};
    int m_attack_range{1};
    int m_movement_range{2};
    coordinates m_coordinates;
    int m_player_index;
    int m_unit_index;

public:
    unit(const coordinates &cell_coordinates, int player_index, int unit_index)
        : m_coordinates(cell_coordinates),
          m_player_index(player_index),
          m_unit_index(unit_index) {
    }

    [[nodiscard]] int get_movement_range() const;
};

}  // namespace game_model

#endif  // MODEL_UNIT_HPP
