#ifndef BATTLE_OF_HEROES_ENUM_CLASSES_FWD_HPP
#define BATTLE_OF_HEROES_ENUM_CLASSES_FWD_HPP

#include "config.hpp"

enum class UnitType { Mushroom, SelectedMushroom };

enum class CellType { Default, Broken };

enum class Fonts { Montserrat };

enum class CellEventType { None, FirstPress, SecondPress, Move };

enum class ButtonType { None, Play, Pass, Menu, Exit };

static std::string source_dir = RESOURCE_PATH;

#endif  // BATTLE_OF_HEROES_ENUM_CLASSES_FWD_HPP
