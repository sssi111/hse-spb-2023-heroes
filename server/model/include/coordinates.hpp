#ifndef MODEL_COORDINATES_HPP
#define MODEL_COORDINATES_HPP

#include "proto/all_protos/demo.grpc.pb.h"

namespace game_model {
class coordinates {
private:
    int m_row;
    int m_column;

public:
    coordinates(int row, int column) : m_row(row), m_column(column) {
    }

    explicit coordinates(const namespace_proto::Cell &cell)
        : m_row(cell.row()), m_column(cell.column()) {
    }

    [[nodiscard]] int get_row() const;
    [[nodiscard]] int get_column() const;
    coordinates operator+(const coordinates &delta) const;
};
}  // namespace game_model

#endif  // MODEL_COORDINATES_HPP
