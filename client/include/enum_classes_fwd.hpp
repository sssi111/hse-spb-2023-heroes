#ifndef BATTLE_OF_HEROES_ENUM_CLASSES_FWD_HPP
#define BATTLE_OF_HEROES_ENUM_CLASSES_FWD_HPP

#include <string>
#include "config.hpp"

namespace game_interface {
enum class UnitType { Empty, UnitType1, UnitType2 };

enum class CellType { Default, Broken, Selected, Enemy, Attack };

enum class TextureType { MenuBackground };

enum class CellEventType { FirstPress, SecondPress, Move, Targeting, Nothing };

enum class ButtonType { None, Play, Pass, Menu, Exit, Skip, GiveUp };
}  // namespace game_interface

namespace menu_interface {
enum class PageType { Game, Exit, Entry, SignUp, Registration, GameChoose };
}  // namespace menu_interface

namespace interface {
static std::string source_dir = RESOURCE_PATH;

enum class Fonts { TittleFont, CaptionFont };
}  // namespace interface

#endif  // BATTLE_OF_HEROES_ENUM_CLASSES_FWD_HPP
