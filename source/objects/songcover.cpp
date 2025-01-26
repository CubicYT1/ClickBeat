#include "../objects.hpp"

#include <iostream>

class objects::SongCover : public game::Object {
private:
    sf::Texture texture;
    sf::Sprite *sprite = nullptr;

public:
    SongCover() {
        visible = true;
        texture.loadFromFile("assets/images/cover.png");
        texture.resize({1000, 1000});

        sprite = new sf::Sprite(texture);
    }

    ~SongCover() {
        delete sprite;
    }

    void update() override {
        sprite->setOrigin({500, 500});

        float scale = (float)window::window.getSize().x / 1000;
        sprite->setScale({scale, scale});

        float yPos = window::window.getSize().y / 2;
        sprite->setPosition({500, yPos});
    }

    sf::Drawable *getDrawable() override {
        return sprite;
    }
};