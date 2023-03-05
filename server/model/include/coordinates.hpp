#ifndef MODEL_COORDINATES_HPP
#define MODEL_COORDINATES_HPP

namespace game_model {
class Coordinates {
private:
    int m_x;
    int m_y;

public:
    Coordinates(int x, int y) : m_x(x), m_y(y) {
    }

    int get_x() const;
    int get_y() const;
    void set_x(int x);
    void set_y(int y);
};
}  // namespace game_model

#endif  // MODEL_COORDINATES_HPP
