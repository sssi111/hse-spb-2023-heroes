#ifndef BATTLE_OF_HEROES_MANAGER_HPP
#define BATTLE_OF_HEROES_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "enum_classes_fwd.hpp"

namespace game_interface {
class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager() = default;

    const sf::Texture &load_cell_texture(CellType texture);

    const sf::Texture &load_cell_frame_texture(CellType texture);

    const sf::Texture &load_unit_texture(UnitType texture);

    const sf::Texture &load_selected_unit_texture(UnitType texture);

    const sf::Texture &load_texture(TextureType texture);

    const sf::Font &load_font(interface::Fonts font);

private:
    std::unordered_map<CellType, sf::Texture> m_cell_textures;
    std::unordered_map<CellType, sf::Texture> m_cell_frame_textures;
    std::unordered_map<UnitType, sf::Texture> m_unit_textures;
    std::unordered_map<UnitType, sf::Texture> m_selected_unit_textures;
    std::unordered_map<TextureType, sf::Texture> m_textures;
    std::unordered_map<interface::Fonts, sf::Font> m_fonts;
};

ResourceManager *resource_manager();
}  // namespace game_interface

#endif  // BATTLE_OF_HEROES_MANAGER_HPP
