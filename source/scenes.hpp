#pragma once
#include "util.hpp"

namespace scenes {
    class Title;
    class Menu;
    class LevelEditor;

    void editor(game::Song);
    void title();
    void menu();
}

#include "scenes/leveleditor.cpp"
#include "scenes/title.cpp"
#include "scenes/menu.cpp"
#include "scenes/functions.cpp"