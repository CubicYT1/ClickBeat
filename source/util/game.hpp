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
        float value = *reference;
    };

    int fps = 100;
    Scene *currentScene = nullptr;
    sf::Music music;
    std::queue<sf::Keyboard::Key> keyQueue;
    std::vector<InterpolationData> interpolationData;

    void update();
    float getDeltaTime();

    namespace player {
        sf::Color bgColor = {0, 0, 150, 255};
    }
};

#include "game/object.cpp"
#include "game/scene.cpp"
#include "game/updater.cpp"
#include "game/deltatime.cpp"