#ifndef MODEL_PLAYER_HPP
#define MODEL_PLAYER_HPP

#include <vector>
#include "board.hpp"
#include "hero.hpp"
#include "unit.hpp"

namespace game_model {

class player {
private:
    std::vector<unit> m_units_list{};
    hero m_hero{};
    int m_id;

public:
    explicit player(int account_id) : m_id(account_id) {
    }

    void set_start_units(int player_index, const board &game_board);
    [[nodiscard]] int get_id() const;
    [[nodiscard]] unit &get_unit(int index);
    virtual ~player() = default;
};

}  // namespace game_model

#endif  // MODEL_PLAYER_HPP
