#ifndef MODEL_CELL_HPP
#define MODEL_CELL_HPP

namespace game_model {

struct Cell {
private:
    int m_health;
    int m_player_index;
    int m_unit_index;

public:
    int get_player_index() const;
    int get_unit_index() const;
    void set_player_index(int player_index);
    void set_unit_index(int unit_index);
};

void move(Cell &current_cell, Cell &new_cell);

}  // namespace game_model

#endif  // MODEL_CELL_HPP
