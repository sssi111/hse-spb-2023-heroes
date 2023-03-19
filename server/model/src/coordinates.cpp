#include "coordinates.hpp"

namespace game_model {
int coordinates::get_row() const {
    return m_row;
}

int coordinates::get_column() const {
    return m_column;
}

coordinates coordinates::operator+(const coordinates &delta) const {
    int row_new = m_row + delta.get_row();
    int column_new = m_column + delta.get_column();
    return {row_new, column_new};
}
}  // namespace game_model