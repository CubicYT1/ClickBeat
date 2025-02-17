#pragma once
#include "../scenes.hpp"

void scenes::title() {
    game::upcomingScene = new scenes::Title();
}

void scenes::editor(game::Song map) {
    game::upcomingScene = new scenes::LevelEditor(map);
}

void scenes::menu() {
    game::upcomingScene = new scenes::Menu();
}