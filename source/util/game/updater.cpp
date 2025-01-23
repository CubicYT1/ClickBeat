#include "../game.hpp"

#include <iostream>

void game::update() {
    currentScene->update();
    for (int i = 0; i < currentScene->objects.getLength(); i++) {
        currentScene->objects.byindex(i)->update();
    }
}