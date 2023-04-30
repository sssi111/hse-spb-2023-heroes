#ifndef MODEL_GAME_HPP
#define MODEL_GAME_HPP

#include <functional>
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
        m_players_list[0]->set_start_units(0, m_board);
        m_players_list[1]->set_start_units(1, m_board);
    }

    [[nodiscard]] board &get_board();
    [[nodiscard]] cell &get_cell(const coordinates &cell_coordinates);
    [[nodiscard]] std::vector<std::reference_wrapper<cell>>
    get_reachable_cells(const coordinates &cell_coordinates, int user_id);
    void move(
        const coordinates &current_cell_coordinates,
        const coordinates &new_cell_coordinates
    );
};

}  // namespace game_model

#endif  // MODEL_GAME_HPP
