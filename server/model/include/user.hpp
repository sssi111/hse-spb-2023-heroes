#ifndef MODEL_USER_HPP
#define MODEL_USER_HPP

#include "player.hpp"

namespace game_model {

class user : public player {
public:
    explicit user(int account_id) : player(account_id) {
    }
};

}  // namespace game_model

#endif  // MODEL_USER_HPP
