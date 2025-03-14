#pragma once
#include <SFML/Graphics.hpp>

namespace window {
    const sf::Vector2u minSize({1000, 800});
    sf::RenderWindow window(sf::VideoMode({800, 600}), "ClickBeat");

    void render();
    void handleEvents();
}

#include "window/renderer.cpp"
#include "window/eventhandler.cpp" 