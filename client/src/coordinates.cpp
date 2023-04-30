#include "coordinates.hpp"

namespace game_view {
[[nodiscard]] int Coords::get_row() const {
    return m_row;
}

[[nodiscard]] int Coords::get_column() const {
    return m_column;
}
}  // namespace game_view