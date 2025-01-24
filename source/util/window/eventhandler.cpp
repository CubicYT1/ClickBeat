#include "../window.hpp"

#include <iostream>

void window::handleEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if (const sf::Event::Resized *resizeEvent = event->getIf<sf::Event::Resized>()) {
            sf::FloatRect viewRect({0, 0}, (sf::Vector2f)resizeEvent->size);
            window.setView(sf::View(viewRect));
        }
        else if (const sf::Event::KeyPressed *keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            std::cout << "Key Pressed: " << (std::string)sf::Keyboard::getDescription(keyEvent->scancode) << "\n";
            game::keyQueue.push(keyEvent->code);
        }
        else if (const sf::Event::MouseMoved *moveEvent = event->getIf<sf::Event::MouseMoved>()) {
            std::cout << "Mouse moved: X:" << moveEvent->position.x << " Y:" << moveEvent->position.y << "\n";
        }
    }
}