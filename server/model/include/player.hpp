#ifndef MODEL_PLAYER_HPP
#define MODEL_PLAYER_HPP

#include <hero.hpp>
#include <unit.hpp>
#include <vector>

namespace game_model {

struct Player {
private:
    std::vector<Unit> m_units_list;
    Hero m_hero;
};

}  // namespace game_model

#endif  // MODEL_PLAYER_HPP
