#include "../../objects.hpp"

class objects::templates::Rect : public game::Object {
private:
    sf::RectangleShape *rectangle;

public:
    Rect(const sf::Vector2f size, const sf::Color color) {
        rectangle = new sf::RectangleShape(size);
        rectangle->setFillColor(color);
    }

    sf::Drawable *getDrawable() {
        return rectangle;
    }
};