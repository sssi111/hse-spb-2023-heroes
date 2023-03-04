#ifndef BATTLE_OF_HEROES_MANAGER_HPP
#define BATTLE_OF_HEROES_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "enum_classes_fwd.hpp"

class ResourceManager {
public:
    ResourceManager();

    const sf::Texture &load_cell_texture(CellTextures texture);

    const sf::Texture &load_unit_texture(UnitTextures texture);

    const sf::Font &load_font(Fonts font);

private:
    std::unordered_map<CellTextures, sf::Texture> m_cell_textures{1};
    std::unordered_map<UnitTextures, sf::Texture> m_unit_textures{1};
    std::unordered_map<Fonts, sf::Font> m_fonts{1};
};

ResourceManager *resource_manager();

#endif  // BATTLE_OF_HEROES_MANAGER_HPP
