#include "coordinates.hpp"

[[nodiscard]] int Coords::get_row() const {
    return m_row;
}

[[nodiscard]] int Coords::get_column() const {
    return m_column;
}
