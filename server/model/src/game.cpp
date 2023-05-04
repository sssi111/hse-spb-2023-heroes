#include "game.hpp"
#include <vector>
#include "cell.hpp"

namespace game_model {

cell &game::get_cell(const coordinates &cell_coordinates) {
    return m_board.get_cell(cell_coordinates);
}

std::vector<std::reference_wrapper<cell>>
game::get_reachable_cells(const coordinates &cell_coordinates, int user_id) {
    int player_id = (m_players_list[0]->get_id() == user_id ? 0 : 1);
    if (!get_cell(cell_coordinates).is_unit_movable(player_id))
        return {};
    int max_distance =
        m_players_list[player_id]
            ->get_unit(m_board.get_cell(cell_coordinates).get_unit_index())
            .get_movement_range();
    return m_board.get_reachable_cells(cell_coordinates, max_distance);
}

std::vector<std::reference_wrapper<cell>>
game::get_attackable_cells(const coordinates &cell_coordinates, int user_id) {
    int player_id = (m_players_list[0]->get_id() == user_id ? 0 : 1);
    if (!get_cell(cell_coordinates).is_unit_movable(player_id))
        return {};
    int max_distance =
        m_players_list[player_id]
            ->get_unit(m_board.get_cell(cell_coordinates).get_unit_index())
            .get_attack_range();
    return m_board.get_attackable_cells(cell_coordinates, max_distance);
}

[[nodiscard]] player *game::get_player(int index) {
    return m_players_list[index].get();
}

void game::move(
    const coordinates &current_cell_coordinates,
    const coordinates &new_cell_coordinates
) {
    cell &current_cell = get_cell(current_cell_coordinates);
    cell &new_cell = get_cell(new_cell_coordinates);
    int player_index = current_cell.get_player_index();
    int unit_index = current_cell.get_unit_index();
    clear_cell(current_cell);
    new_cell.set_player_index(player_index);
    new_cell.set_unit_index(unit_index);
    new_cell.decrease_cell_durability(
        get_player(player_index)->get_unit(unit_index).get_weight()
    );
}

void game::attack(const coordinates &attacking, const coordinates &attacked) {
    cell &attacking_cell = get_cell(attacking);
    cell &attacked_cell = get_cell(attacked);
    attack_cell(attacking_cell, attacked_cell);
}

void game::attack_cell(const cell &attacking, cell &attacked) {
    unit &attacking_unit =
        m_players_list[attacking.get_player_index()]->get_unit(
            attacking.get_unit_index()
        );
    unit &attacked_unit = m_players_list[attacked.get_player_index()]->get_unit(
        attacked.get_unit_index()
    );
    attacked_unit.decrease_health(attacking_unit.get_damage());
    if (attacked_unit.is_dead())
        clear_cell(attacked);
}

void game::clear_cell(cell &current_cell) {
    current_cell.set_player_index(-1);
    current_cell.set_unit_index(-1);
}
}  // namespace game_model
