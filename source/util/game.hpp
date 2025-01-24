#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <queue>

namespace game {
    class Object;
    class Scene;

    int fps = 100;
    Scene *currentScene = nullptr;
    sf::Music music;
    std::queue<sf::Keyboard::Key> keyQueue;

    void update();
    float getDeltaTime();
};

#include "game/object.cpp"
#include "game/scene.cpp"
#include "game/updater.cpp"
#include "game/deltatime.cpp"