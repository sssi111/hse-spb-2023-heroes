#ifndef BATTLE_OF_HEROES_ENUM_CLASSES_FWD_HPP
#define BATTLE_OF_HEROES_ENUM_CLASSES_FWD_HPP

#include <string>
#include "config.hpp"

namespace game_view {
enum class UnitType { Empty, Mushroom, SelectedMushroom };

enum class CellType { Default, Broken, Selected };

enum class Fonts { Montserrat };

enum class CellEventType { FirstPress, SecondPress, Move, Targeting, Nothing };

enum class ButtonType { None, Play, Pass, Menu, Exit };

static std::string source_dir = RESOURCE_PATH;
}  // namespace game_view

namespace menu_view {

enum class PageType { Hehe, Exit, Entry, Login, Registration, GameChoose };



}

#endif  // BATTLE_OF_HEROES_ENUM_CLASSES_FWD_HPP
