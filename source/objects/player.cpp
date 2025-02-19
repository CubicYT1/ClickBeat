#include "../objects.hpp"

class objects::Player : public objects::templates::Sprite {
public:
    Player() : templates::Sprite("assets/images/player.png") {
        util::setOriginCenter((sf::Sprite&)*this->getDrawable());
    }

    void update() override {
        sf::Sprite *sprite = (sf::Sprite*)this->getDrawable();

        sprite->setPosition({game::mousePosition.x, (float)window::window.getSize().y * 0.8});

        float scale = (float)window::window.getSize().x / 15 / sprite->getTexture().getSize().x;
        sprite->setScale({scale, scale});
    }
};