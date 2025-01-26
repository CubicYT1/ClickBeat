#pragma
#include "../objects.hpp"

class objects::TitleText : public game::Object {
private:
    sf::Text *text;
    sf::Font font;

public:
    TitleText() {
        font.openFromFile("assets/fonts/bold italic.ttf");
        text = new sf::Text(font, "Press [Space] to begin");

        text->setOrigin({text->getGlobalBounds().size.x / 2, 0});
        text->setFillColor({255, 255, 255, 100});
    }

    ~TitleText() {
        delete text;
    }

    void update() override {
        sf::Vector2u winSize = window::window.getSize();
        text->setPosition({winSize.x / 2, winSize.y - 100});
    }

    sf::Drawable *getDrawable() override {
        return text;
    }
};