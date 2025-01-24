#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace game {
    class Object;
    class Scene;

    Scene *currentScene = nullptr;
    sf::Music music;

    void update();
};

#include "game/object.cpp"
#include "game/scene.cpp"
#include "game/updater.cpp"