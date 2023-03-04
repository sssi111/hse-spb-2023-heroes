#include "resource_manager.hpp"
#include <SFML/Graphics.hpp>

ResourceManager *resource_manager() {
    static ResourceManager resource_manager;
    return &resource_manager;
}

ResourceManager::ResourceManager() {
    // load cell textures
    m_cell_textures[CellTextures::Default].loadFromFile(
        source_dir + "grass.jpg"
    );

    // load unit texture
    m_unit_textures[UnitTextures::Default].loadFromFile(
        source_dir + "hero.png"
    );

    // load fonts
    m_fonts[Fonts::Montserrat].loadFromFile(
        source_dir + "Montserrat-SemiBold.otf"
    );
}

const sf::Texture &ResourceManager::load_cell_texture(CellTextures texture) {
    return m_cell_textures[texture];
}

const sf::Texture &ResourceManager::load_unit_texture(UnitTextures texture) {
    return m_unit_textures[texture];
}

const sf::Font &ResourceManager::load_font(Fonts font) {
    return m_fonts[font];
}
