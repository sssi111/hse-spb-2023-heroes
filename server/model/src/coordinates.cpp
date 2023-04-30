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

bool coordinates::operator==(const coordinates &other_coordinates) const {
    return m_row == other_coordinates.get_row() &&
           m_column == other_coordinates.get_column();
}
}  // namespace game_model