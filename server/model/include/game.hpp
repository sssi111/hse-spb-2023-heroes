#ifndef MODEL_GAME_HPP
#define MODEL_GAME_HPP

#include <memory>
#include <utility>
#include <vector>
#include "board.hpp"
#include "cell.hpp"
#include "player.hpp"
#include "user.hpp"

namespace game_model {

class game {
private:
    std::vector<std::unique_ptr<player>> m_players_list;
    board m_board{};

public:
    explicit game(int account_id_first, int account_id_second) {
        m_players_list.emplace_back(std::make_unique<user>(account_id_first));
        m_players_list.emplace_back(std::make_unique<user>(account_id_second));
    }

    [[nodiscard]] board get_board() const;
    [[nodiscard]] cell get_cell(const coordinates &cell_coordinates) const;
    [[nodiscard]] std::vector<cell>
    get_reachable_cells(const coordinates &cell_coordinates, int user_id);
};

}  // namespace game_model

#endif  // MODEL_GAME_HPP
