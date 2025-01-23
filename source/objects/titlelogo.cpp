#include "../objects.hpp"

#include <iostream>

class objects::TitleLogo : public game::Object {
private:
    sf::Texture texture;
    sf::Sprite sprite;

public:
    TitleLogo() : sprite(texture) {
        zIndex = 0;
        texture = sf::Texture("assets/images/logo.png");
    }

    sf::Drawable &getDrawable() override {
        return sprite;
    }

    void update() override {
        sprite.setPosition({window::window.getSize().x / 2, 100});
    }
};