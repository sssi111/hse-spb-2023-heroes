#ifndef MODEL_CELL_HPP
#define MODEL_CELL_HPP

namespace game_model {

struct Cell {
private:
    int m_health;
    int m_player_index;
    int m_unit_index;
};

}  // namespace game_model

#endif  // MODEL_CELL_HPP
