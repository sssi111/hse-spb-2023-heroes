#ifndef BATTLE_OF_HEROES_COORDINATES_HPP
#define BATTLE_OF_HEROES_COORDINATES_HPP

namespace game_interface {
class Coords {
public:
    Coords() = default;
    Coords(int row, int column) : m_row(row), m_column(column){};
    ~Coords() = default;

    [[nodiscard]] int get_row() const;
    [[nodiscard]] int get_column() const;

private:
    int m_row{0};
    int m_column{0};
};
}  // namespace game_interface

#endif  // BATTLE_OF_HEROES_COORDINATES_HPP
