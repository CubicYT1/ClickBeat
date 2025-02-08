#include "scenes.hpp"
#include "util.hpp"

#include <iostream>

int main(int argc, std::string argv[]) {
    window::window.setMinimumSize(window::minSize);

    if (argc == 1) {
       game::currentScene = new scenes::Title(); 
    }
    else {
        game::currentScene = new scenes::LevelEditor();
    }
    
    
    while (window::window.isOpen()) {
        window::handleEvents();
        game::update();
        window::render();
        
        sf::sleep(sf::seconds(game::getDeltaTime()));
    }
    return 0;
}