#include "util.hpp"
#include "scenes.hpp"

#include <iostream>

int main() {
    window::window.setMinimumSize(window::minSize);
    game::currentScene = new scenes::Title();
    
    while (window::window.isOpen()) {
        window::handleEvents();
        game::update();
        window::render();
    }
    return 0;
}