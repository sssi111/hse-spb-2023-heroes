#ifndef MODEL_GAME_HPP
#define MODEL_GAME_HPP

#include <board.hpp>
#include <memory>
#include <player.hpp>
#include <vector>

namespace game_model {

struct Game {
private:
    std::vector<std::unique_ptr<Player>> m_players_list;
    Board m_board;
    int m_current_player_index = 0;

public:
    Game(
        const std::vector<std::unique_ptr<Player>> &players_list,
        const &Board board
    )
        : m_players_list(players_list), m_board(board) {
    }
    bool can_move(int player_index);
    void change_player();
    bool can_choose_cell();
};

}  // namespace game_model

#endif  // MODEL_GAME_HPP
