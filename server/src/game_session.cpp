#include "server.hpp"

void start_game_session(int game_id) {
    GameSession *game_session = &(get_server_state()->game_sessions[game_id]);

    Player first_player = game_session->get_first_player();
    Player second_player = game_session->get_second_player();
    std::unordered_map<int, TSQueue<namespace_proto::GameState>>
        *response_queues_ref = game_session->get_response_queues();
    namespace_proto::GameState *game_state_ref = game_session->get_game_state();

    for (int i = 0; i < 100; ++i) {
        namespace_proto::Cell *new_cell = game_state_ref->add_game_cells();
        new_cell->set_allocated_unit(nullptr);
        new_cell->set_id_hero(-1);
        new_cell->set_x(i % 10);
        new_cell->set_y(i / 10);
    }

    game_state_ref->set_game_id(game_id);
    (*response_queues_ref)[first_player.get_id()].push(*game_state_ref);
    (*response_queues_ref)[second_player.get_id()].push(*game_state_ref);

    std::thread first_writer([response_queues_ref, &first_player]() {
        while (true) {
            if ((*response_queues_ref)[first_player.get_id()].size() > 0) {
                namespace_proto::GameState response =
                    (*response_queues_ref)[first_player.get_id()].pop();
                first_player.get_stream()->Write(response);
            }
        }
    });

    std::thread second_writer([response_queues_ref, &second_player]() {
        while (true) {
            if ((*response_queues_ref)[second_player.get_id()].size() > 0) {
                namespace_proto::GameState response =
                    (*response_queues_ref)[second_player.get_id()].pop();
                second_player.get_stream()->Write(response);
            }
        }
    });

    first_writer.join();
    second_writer.join();
}