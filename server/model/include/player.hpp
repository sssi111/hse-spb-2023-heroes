#ifndef MODEL_PLAYER_HPP
#define MODEL_PLAYER_HPP

#include "hero.hpp"
#include "unit.hpp"
#include <vector>

namespace game_model {

struct Player {
private:
    std::vector<Unit> m_units_list;
    Hero m_hero;
    int id;
public:
    int get_id() const;
    Unit get_unit(int index) const;
};

}  // namespace game_model

#endif  // MODEL_PLAYER_HPP
