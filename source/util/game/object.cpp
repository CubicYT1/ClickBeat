#include "../game.hpp"

class game::Object {
public:
    int zIndex = 0;
    bool visible = true;

    virtual void update() {}
    virtual sf::Drawable &getDrawable() {}
};