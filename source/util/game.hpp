#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <queue>
#include <vector>

namespace game {
    class Object;
    class Scene;

    struct InterpolationData {
        int *reference;
        int target;
        int speed; 
        int added = 0;
        float decimal = 0;
        int original = *reference;
    };

    int fps = 100;
    Scene *currentScene = nullptr;
    sf::Music music;
    std::queue<sf::Keyboard::Key> keyQueue;
    std::vector<InterpolationData> interpolationData;

    void update();
    float getDeltaTime();

    namespace player {
        sf::Color bgColor = {150, 0, 0, 255};
    }
};

#include "game/object.cpp"
#include "game/scene.cpp"
#include "game/updater.cpp"
#include "game/deltatime.cpp"