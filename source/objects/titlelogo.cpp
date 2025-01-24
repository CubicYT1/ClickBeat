#include "../objects.hpp"

#include <iostream>

class objects::TitleLogo : public game::Object {
private:
    sf::Texture texture;
    sf::Sprite *sprite = nullptr;

public:
    TitleLogo() {
        texture = sf::Texture("assets/images/logo.png");
        sprite = new sf::Sprite(texture);

        sf::Vector2u textureSize = texture.getSize();
        sprite->setOrigin({textureSize.x / 2, textureSize.y / 2});
    }

    ~TitleLogo() {
        delete sprite;
    }

    sf::Drawable *getDrawable() override {
        return sprite;
    }

    void update() override {
       sf::Vector2u winSize = window::window.getSize();
       sf::Vector2u textureSize = texture.getSize();

       float scale = (float)winSize.y / textureSize.y / 1.5;
       sprite->setScale({scale, scale});

       sprite->setPosition({winSize.x / 2, (float)winSize.y / 2});
    }
};