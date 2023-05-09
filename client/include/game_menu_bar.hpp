#ifndef BATTLE_OF_HEROES_GAME_MENU_BAR_HPP
#define BATTLE_OF_HEROES_GAME_MENU_BAR_HPP

#include "spell.hpp"

namespace game_interface {

class GameMenuBar {
public:
    GameMenuBar(sf::Vector2f wind_size, float menu_height);
    ~GameMenuBar() = default;

    void set_spells_to_default();
    void update(sf::Event event, Window *window);
    void render(sf::RenderWindow *window);
private:

    sf::RectangleShape m_turn_label;
    sf::Text m_data;
    std::vector<MenuButton> m_buttons;
    int m_spells_amount;
    std::vector<Spell> m_spells;
    int m_opponents_spells_amount;
    std::vector<Spell> m_opponents_spells;

    void update_turn(const std::string &new_label);
};
}  // namespace game_interface

#endif  // BATTLE_OF_HEROES_GAME_MENU_BAR_HPP
