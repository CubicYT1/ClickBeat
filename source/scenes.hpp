#pragma once
#include "util.hpp"

namespace scenes {
    class Title;
    class Menu;
    class LevelEditor;
    class Level;

    void editor();
    void title();
    void menu();
    void level();
}

#include "scenes/leveleditor.cpp"
#include "scenes/title.cpp"
#include "scenes/menu.cpp"
#include "scenes/level.cpp"
#include "scenes/functions.cpp"