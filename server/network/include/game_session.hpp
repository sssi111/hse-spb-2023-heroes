#ifndef GAME_SESSION_HPP
#define GAME_SESSION_HPP

#include "TSqueue.hpp"
#include "attack_interactor.hpp"
#include "attack_select_interactor.hpp"
#include "game.hpp"
#include "move_interactor.hpp"
#include "move_select_interactor.hpp"
#include "proto/all_protos/demo.grpc.pb.h"
#include "spell_interactor.hpp"
#include "spell_select_interactor.hpp"

class Player final {
    int id;
    ::grpc::ServerWriter<namespace_proto::GameState> *stream;

public:
    Player(int id, ::grpc::ServerWriter<namespace_proto::GameState> *stream)
        : id(id), stream(stream) {
    }

    [[nodiscard]] int get_id() const {
        return id;
    }

    [[nodiscard]] ::grpc::ServerWriter<namespace_proto::GameState> *get_stream(
    ) const {
        return stream;
    }
};

class GameSession {
    Player first_player;
    Player second_player;
    std::unordered_map<int, TSQueue<namespace_proto::GameState>>
        response_queues;
    namespace_proto::GameState game_state;
    game_model::game model_game;
    interactors::mover mover;
    interactors::attacker attacker;
    interactors::move_selecter move_selecter;
    interactors::attack_selecter attack_selecter;
    interactors::speller speller;
    interactors::spell_selecter spell_selecter;

public:
    GameSession(Player first_player_, Player second_player_)
        : first_player(first_player_),
          second_player(second_player_),
          model_game(first_player_.get_id(), second_player_.get_id()),
          mover(model_game),
          move_selecter(model_game),
          attacker(model_game),
          attack_selecter(model_game),
          speller(model_game),
          spell_selecter(model_game) {
    }

    Player get_first_player() const {
        return first_player;
    }

    Player get_second_player() const {
        return second_player;
    }

    std::unordered_map<int, TSQueue<namespace_proto::GameState>>
        *get_response_queues() {
        return &response_queues;
    }

    namespace_proto::GameState *get_game_state() {
        return &game_state;
    }

    game_model::game *get_model_game() {
        return &model_game;
    }

    interactors::mover *get_mover() {
        return &mover;
    }

    interactors::move_selecter *get_move_selecter() {
        return &move_selecter;
    }

    interactors::attacker *get_attacker() {
        return &attacker;
    }

    interactors::attack_selecter *get_attack_selecter() {
        return &attack_selecter;
    }

    interactors::spell_selecter *get_spell_selecter(){
        return &spell_selecter;
    }

    interactors::speller *get_speller(){
        return &speller;
    }

};

void start_game_session(int game_id);

#endif  // GAME_SESSION_HPP
