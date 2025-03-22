#pragma once
#include <SFML/Graphics.hpp>

namespace window {
    const sf::Vector2u minSize({1366, 768});
    sf::RenderWindow window(sf::VideoMode({800, 600}), "ClickBeat");

    void render();
    void initRender();
    void handleEvents();
    void initCircles();
}

#include "window/renderer.cpp"
#include "window/eventhandler.cpp" 