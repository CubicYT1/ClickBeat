#pragma once
#include <SFML/Graphics.hpp>

namespace util {
    template <typename Key, typename Val> class Dictionary;

    void setOriginCenter(sf::Sprite&);
    void doNothing();
    int randomInt(int, int);
}

#include "util/dictionary.cpp"
#include "util/functions.cpp"