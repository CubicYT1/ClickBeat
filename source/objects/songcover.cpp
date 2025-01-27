#include "../objects.hpp"

#include <iostream>

class objects::SongCover : public game::Object {
private:
    sf::Texture texture;
    sf::Sprite *sprite = nullptr;

public:
    int scaledSizeX;

    SongCover() {
        visible = true;
        texture.loadFromFile("assets/images/cover.png");

        sprite = new sf::Sprite(texture);
    }

    ~SongCover() {
        delete sprite;
    }

    void update() override {
        sf::Vector2f winSize = (sf::Vector2f)window::window.getSize();
        sf::Vector2f textureSize = (sf::Vector2f)texture.getSize();

        float scaleX = winSize.x / textureSize.x / 5;
        float scaleY = winSize.x / textureSize.y / 5;
        scaledSizeX = textureSize.x * scaleX;

        sprite->setScale({scaleX, scaleY});

        float yPos = window::window.getSize().y / 2 - textureSize.y * scaleY / 2;
        sprite->setPosition({30, 30});
    }

    sf::Drawable *getDrawable() override {
        return sprite;
    }
};