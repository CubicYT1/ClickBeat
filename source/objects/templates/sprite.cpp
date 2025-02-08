#pragma once
#include "../../objects.hpp"

class objects::templates::Sprite : public game::Object {
private:
    sf::Texture texture;
    sf::Sprite *sprite;

public:
    Sprite(const std::string path) {
        texture = sf::Texture(path);
        sprite = new sf::Sprite(texture);
    }

    ~Sprite() {
        delete sprite;
    }

    sf::Drawable *getDrawable() override {
        return sprite;
    }

    void changeTexture(const std::string path) {
        texture = sf::Texture(path);
        sprite->setTexture(texture);
    }
};