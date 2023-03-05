#include "coordinates.hpp"

namespace game_model {
int Coordinates::get_x() const {
    return m_x;
}

int Coordinates::get_y() const {
    return m_y;
}

void Coordinates::set_x(int x) {
    m_x = x;
}

void Coordinates::set_y(int y) {
    m_y = y;
}
}  // namespace game_model