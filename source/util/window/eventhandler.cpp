#include "../window.hpp"

#include <iostream>

void window::handleEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if (const sf::Event::Resized *resizeEvent = event->getIf<sf::Event::Resized>()) {
            sf::FloatRect viewRect({0, 0}, (sf::Vector2f)resizeEvent->size);
            if (resizeEvent->size.x > (float)resizeEvent->size.y / 9 * 16) {
                viewRect = sf::FloatRect({0, 0}, {(float)resizeEvent->size.y / 9 * 16, resizeEvent->size.y});
                window::window.setSize({(float)resizeEvent->size.y / 9 * 16, resizeEvent->size.y});
            }

            window.setView(sf::View(viewRect));
        }
        else if (const sf::Event::KeyPressed *keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            std::cout << "Key Pressed: " << (std::string)sf::Keyboard::getDescription(keyEvent->scancode) << "\n";
            game::keyQueue.push(keyEvent->code);
        }
        else if (const sf::Event::MouseMoved *moveEvent = event->getIf<sf::Event::MouseMoved>()) {
            std::cout << "Mouse moved: X:" << moveEvent->position.x << " Y:" << moveEvent->position.y << "\n";
            game::mousePosition = moveEvent->position;
        }
        else if (const sf::Event::MouseButtonPressed *mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
            std::cout << "Mouse button pressed\n";
            game::mouseQueue.push(mouseEvent->button);
        }
    }
}