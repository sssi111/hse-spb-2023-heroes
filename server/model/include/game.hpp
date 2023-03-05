#ifndef MODEL_GAME_HPP
#define MODEL_GAME_HPP

#include <memory>
#include <vector>
#include "board.hpp"
#include "cell.hpp"
#include "player.hpp"

namespace game_model {

struct Game {
private:
    std::vector<std::unique_ptr<Player>> m_players_list;
    Board m_board;
    int m_current_player_index = 0;

public:
    Game(std::vector<std::unique_ptr<Player>> players_list, const Board &board)
        : m_players_list(std::move(players_list)), m_board(board) {
    }

    bool is_can_move(int player_index);
    void change_player();
    Board get_board() const;
    Cell &get_cell(Coordinates cell_coordinates) const;
    std::vector<Cell> reachable_cells(Coordinates cell_coordinates, int id)
        const;
};

}  // namespace game_model

#endif  // MODEL_GAME_HPP
