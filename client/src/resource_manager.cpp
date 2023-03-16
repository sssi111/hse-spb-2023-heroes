#include "resource_manager.hpp"
#include <SFML/Graphics.hpp>

ResourceManager *resource_manager() {
    static ResourceManager resource_manager;
    return &resource_manager;
}

ResourceManager::ResourceManager() {
    m_cell_textures[CellType::Default].loadFromFile(source_dir + "grass.jpg");

    m_unit_textures[UnitType::Mushroom].loadFromFile(source_dir + "hero.png");
    m_unit_textures[UnitType::SelectedMushroom].loadFromFile(source_dir + "selected_hero.png");

    m_fonts[Fonts::Montserrat].loadFromFile(
        source_dir + "Montserrat-SemiBold.otf"
    );
}

const sf::Texture &ResourceManager::load_cell_texture(CellType texture) {
    return m_cell_textures[texture];
}

const sf::Texture &ResourceManager::load_unit_texture(UnitType texture) {
    return m_unit_textures[texture];
}

const sf::Font &ResourceManager::load_font(Fonts font) {
    return m_fonts[font];
}
