#include "../window.hpp"

void window::handleEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if (const sf::Event::Resized *resizeEvent = event->getIf<sf::Event::Resized>()) {
            sf::FloatRect viewRect({0, 0}, (sf::Vector2f)resizeEvent->size);
            window.setView(sf::View(viewRect));
        }
    }
}