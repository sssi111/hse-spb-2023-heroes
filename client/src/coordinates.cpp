#include "coordinates.hpp"

namespace game_interface {
[[nodiscard]] int Coords::get_row() const {
    return m_row;
}

[[nodiscard]] int Coords::get_column() const {
    return m_column;
}
}  // namespace game_interface