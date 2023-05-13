#include "resource_manager.hpp"
#include <SFML/Graphics.hpp>

namespace game_interface {
[[nodiscard]] ResourceManager *resource_manager() {
    static ResourceManager resource_manager;
    return &resource_manager;
}

ResourceManager::ResourceManager() {
    m_cell_textures[CellType::Default].loadFromFile(
        interface::source_dir + "grass.jpg"
    );
    m_cell_textures[CellType::Broken].loadFromFile(
        interface::source_dir + "grass_broken.jpg"
    );

    m_cell_property_textures[CellType::Default].loadFromFile(
        interface::source_dir + "default.png"
    );
    m_cell_property_textures[CellType::Move].loadFromFile(
        interface::source_dir + "move.png"
    );
    m_cell_property_textures[CellType::Enemy].loadFromFile(
        interface::source_dir + "enemy.png"
    );
    m_cell_property_textures[CellType::Attack].loadFromFile(
        interface::source_dir + "attack.png"
    );
    m_cell_property_textures[CellType::Spell].loadFromFile(
        interface::source_dir + "spell.png"
    );
    m_cell_property_textures[CellType::AttackSpell].loadFromFile(
        interface::source_dir + "attack.png"
    );

    m_unit_textures[UnitType::UnitType1].loadFromFile(
        interface::source_dir + "hero.png"
    );
    m_unit_textures[UnitType::UnitType2].loadFromFile(
        interface::source_dir + "hero2.png"
    );

    m_selected_unit_textures[UnitType::UnitType1].loadFromFile(
        interface::source_dir + "selected_hero.png"
    );
    m_selected_unit_textures[UnitType::UnitType2].loadFromFile(
        interface::source_dir + "selected_hero2.png"
    );

    m_textures[TextureType::MenuBackground].loadFromFile(
        interface::source_dir + "menu_background.jpg"
    );

    m_fonts[interface::Fonts::CaptionFont].loadFromFile(
        interface::source_dir + "caption_font.otf"
    );
    m_fonts[interface::Fonts::TittleFont].loadFromFile(
        interface::source_dir + "tittle_font.otf"
    );

    m_cursors[CursorType::Attack].loadFromFile(
        interface::source_dir + "sword.png"
    );
}

[[nodiscard]] const sf::Texture &ResourceManager::load_cell_texture(
    CellType texture
) {
    return m_cell_textures[texture];
}

[[nodiscard]] const sf::Texture &ResourceManager::load_cell_property_texture(
    CellType texture
) {
    return m_cell_property_textures[texture];
}

[[nodiscard]] const sf::Texture &ResourceManager::load_unit_texture(
    UnitType texture
) {
    return m_unit_textures[texture];
}

[[nodiscard]] const sf::Texture &ResourceManager::load_selected_unit_texture(
    UnitType texture
) {
    return m_selected_unit_textures[texture];
}

[[nodiscard]] const sf::Font &ResourceManager::load_font(interface::Fonts font
) {
    return m_fonts[font];
}

[[nodiscard]] const sf::Texture &ResourceManager::load_texture(
    TextureType texture
) {
    return m_textures[texture];
}

const sf::Image &ResourceManager::load_cursor(CursorType cursor) {
    return m_cursors[cursor];
}
}  // namespace game_interface