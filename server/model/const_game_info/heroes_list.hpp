#ifndef HEROES_LIST_HPP
#define HEROES_LIST_HPP

#include <vector>
#include "hero.hpp"

namespace const_game_info {
const std::vector<game_model::hero> HEROES_LIST = {
    game_model::hero(1, {0, 0}), game_model::hero(2, {0, 0, 0})};
}

#endif  // HEROES_LIST_HPP
