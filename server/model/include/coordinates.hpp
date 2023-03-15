#ifndef MODEL_COORDINATES_HPP
#define MODEL_COORDINATES_HPP

namespace game_model {
class coordinates {
private:
    int m_x;
    int m_y;

public:
    coordinates(int x, int y) : m_x(x), m_y(y) {
    }

    [[nodiscard]] int get_x() const;
    [[nodiscard]] int get_y() const;
    coordinates operator+(const coordinates &delta) const;
};
}  // namespace game_model

#endif  // MODEL_COORDINATES_HPP
