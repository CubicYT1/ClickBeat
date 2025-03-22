#include "../util.hpp"

void util::setOriginCenter(sf::Sprite &sprite) {
    const sf::Vector2u textureSize = sprite.getTexture().getSize();
    sprite.setOrigin({textureSize.x / 2, textureSize.y / 2});
}

void util::doNothing() {}

int util::randomInt(const int min, const int max) {
    static bool first = true;
    if (first) {
        first = false;
        std::srand(std::time(NULL));
    }

    return min + rand() % (max - min + 1);
}