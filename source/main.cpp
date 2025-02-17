#include "scenes.hpp"
#include "util.hpp"

#include <iostream>

int main() {
    window::window.setMinimumSize(window::minSize);
    game::currentScene = new scenes::Title();
    game::clock.start();
    
    while (window::window.isOpen()) {
        window::handleEvents();
        game::update();
        window::render();
        
        if (game::upcomingScene != nullptr) {
            delete game::currentScene;
            game::currentScene = game::upcomingScene;
            game::upcomingScene = nullptr;
        }

        sf::sleep(sf::seconds(game::getDeltaTime()));
    }
    return 0;
}
