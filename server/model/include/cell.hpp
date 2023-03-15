#ifndef MODEL_CELL_HPP
#define MODEL_CELL_HPP
#include "coordinates.hpp"

namespace game_model {

class cell {
private:
    int m_health = 10;
    int m_player_index = -1;
    int m_unit_index = -1;
    coordinates m_coordinates{0, 0};

public:
    cell() = default;

    [[nodiscard]] int get_player_index() const;
    [[nodiscard]] int get_unit_index() const;
    [[nodiscard]] coordinates get_coordinates() const;
    void set_player_index(int player_index);
    void set_unit_index(int unit_index);
    void set_coordinates(const coordinates &coordinates_new);
    static void move(cell &current_cell, cell &new_cell);
};

}  // namespace game_model

#endif  // MODEL_CELL_HPP
