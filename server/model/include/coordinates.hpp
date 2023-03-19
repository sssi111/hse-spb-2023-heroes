#ifndef MODEL_COORDINATES_HPP
#define MODEL_COORDINATES_HPP

#include "proto/all_protos/demo.grpc.pb.h"

namespace game_model {
class coordinates {
private:
    int m_row;
    int m_y;

public:
    coordinates(int x, int y) : m_row(x), m_y(y) {
    }

    explicit coordinates(const namespace_proto::Cell &cell)
        : m_row(cell.row()), m_y(cell.column()) {
    }

    [[nodiscard]] int get_x() const;
    [[nodiscard]] int get_y() const;
    coordinates operator+(const coordinates &delta) const;
};
}  // namespace game_model

#endif  // MODEL_COORDINATES_HPP
