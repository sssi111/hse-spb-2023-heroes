#ifndef GAME_BOT_HPP
#define GAME_BOT_HPP

#include <memory>
#include "game.hpp"

namespace bot {
enum class bot_response_type { SINGLE_CELL, PAIR_OF_CELLS };

class bot_response {
private:
    bot_response_type type;
    game_model::cell from;
    game_model::cell to;

public:
    const bot_response_type &get_type() const {
        return type;
    }

    void set_type(bot_response_type n_type) {
        type = n_type;
    }

    const game_model::cell &get_from_cell() const {
        return from;
    }

    void set_from_cell(const game_model::cell &cell) {
        from = cell;
    }

    const game_model::cell &get_to_cell() const {
        return to;
    }

    void set_to_cell(const game_model::cell &cell) {
        to = cell;
    }
};

class game_bot {
private:
    game_model::game &m_game;

public:
    explicit game_bot(game_model::game &current_game_state)
        : m_game(current_game_state) {
    }

    std::vector<std::reference_wrapper<bot_response>> operator()();
};
}  // namespace bot

#endif  // GAME_BOT_HPP
