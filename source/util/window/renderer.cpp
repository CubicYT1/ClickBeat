#include "../window.hpp"

static sf::Texture bgTexture("assets/images/gradient.png");
static sf::Sprite bg(bgTexture);

void window::render() {
    window.clear();
    
    {
        float scaleX = (float)window::window.getSize().x / bg.getTexture().getSize().x;
        float scaleY = (float)window::window.getSize().y / bg.getTexture().getSize().y;
        bg.setScale({scaleX, scaleY});

        bg.setColor(game::player::bgColor);
    }
    window.draw(bg);

    int lowestZ = 0;
    int highestZ = 0;
    for (int i = 0; i < game::currentScene->objects.getLength(); i++) {
        const int objectZ = game::currentScene->objects.byIndex(i)->zIndex;
        if (objectZ < lowestZ) {
            lowestZ = objectZ;
        }
        else if (objectZ > highestZ) {
            highestZ = objectZ;
        }
    }

    for (int zIndex = lowestZ; zIndex <= highestZ; zIndex++) {
        for (int i = 0; i < game::currentScene->objects.getLength(); i++) {
            if (game::currentScene->objects.byIndex(i)->zIndex == zIndex && game::currentScene->objects.byIndex(i)->visible) {
                window.draw(*game::currentScene->objects.byIndex(i)->getDrawable());
            }
        }
    }

    window.display();
}