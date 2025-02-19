#include "../game.hpp"

static sf::RectangleShape *rect = new sf::RectangleShape({0, 0});

class game::Object {
public:
    int zIndex = 0;
    bool visible = true;

    virtual void update() {}
    
    virtual sf::Drawable *getDrawable() {
        return rect;
    }
};