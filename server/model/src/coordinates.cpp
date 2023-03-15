#include "coordinates.hpp"

namespace game_model {
int coordinates::get_x() const {
    return m_x;
}

int coordinates::get_y() const {
    return m_y;
}

coordinates coordinates::operator+(const coordinates &delta) const {
    int x_new = m_x + delta.get_x();
    int y_new = m_y + delta.get_y();
    return {x_new, y_new};
}
}  // namespace game_model