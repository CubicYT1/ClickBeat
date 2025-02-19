#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <queue>
#include <vector>

namespace game {
    class Object;
    class Scene;
    class Song;

    struct InterpolationData {
        int *reference;
        int target;
        int speed; 
        int added = 0;
        float decimal = 0;
        int original = *reference;
    };

    int fps = 240;
    Scene *currentScene = nullptr;
    Scene *upcomingScene = nullptr;
    sf::Music music;
    std::queue<sf::Keyboard::Key> keyQueue;
    std::queue<sf::Mouse::Button> mouseQueue;
    std::vector<InterpolationData> interpolationData;
    sf::Vector2i mousePosition;
    sf::Clock sceneClock; 

    void update();
    void title();
    void menu();
    void editor();
    float getDeltaTime();
    std::vector<Song> getSongs();   

    namespace player {
        sf::Color bgColor = {0, 0, 150, 255};
    }
}

#include "game/object.cpp"
#include "game/scene.cpp"
#include "game/updater.cpp"
#include "game/functions.cpp"
#include "game/song.cpp"
