#pragma once
#include "../scenes.hpp"

static void resetClock() {
    game::sceneClock.restart();
}

void scenes::title() {
    game::upcomingScene = new scenes::Title();
    resetClock();
}

void scenes::editor() {
    game::upcomingScene = new scenes::LevelEditor(*game::mapToLoad);
    resetClock();
    std::cout << "wadafak";
}

void scenes::menu() {
    game::upcomingScene = new scenes::Menu();
    resetClock();
}

void scenes::level() {
    game::upcomingScene = new scenes::Level(*game::mapToLoad);
    resetClock();
}