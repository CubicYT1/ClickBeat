#include "../window.hpp"
#include "../../util.hpp"

struct Square {
    sf::RectangleShape square;
};

static sf::Texture bgTexture("assets/images/gradient.png");
static sf::Sprite bg(bgTexture);

static sf::CircleShape circles[25];

static void resetCircle(sf::CircleShape &circle) {
    float xPos = (float)util::randomInt(0, 100) / 100;
    int yPos = util::randomInt(-window::window.getSize().y, -25);

    circle.setRadius(50);
    circle.setOrigin(circle.getLocalBounds().getCenter());
    circle.setPosition({xPos, yPos});
    circle.setFillColor({255, 255, 255, 25});
}

void window::initCircles() {
    for (sf::CircleShape &circle : circles) {
        resetCircle(circle);
    }
}

void window::render() {
    window.clear();
    
    {
        float scaleX = (float)window::window.getSize().x / bg.getTexture().getSize().x;
        float scaleY = (float)window::window.getSize().y / bg.getTexture().getSize().y;
        bg.setScale({scaleX, scaleY});

        bg.setColor(game::player::bgColor);
    }
    window.draw(bg);

    for (sf::CircleShape &circle : circles) {
        sf::CircleShape newCircle = circle;
        newCircle.setPosition({circle.getPosition().x * window::window.getSize().x, circle.getPosition().y});

        window.draw(newCircle);

        circle.setPosition({circle.getPosition().x, circle.getPosition().y + (200 * game::getDeltaTime())});

        if (circle.getPosition().y >= window::window.getSize().y + 100) {
            resetCircle(circle);
        }
    }

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