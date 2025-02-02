#include "../game.hpp"

#include <iostream>
#include <algorithm>

void game::update() {
    currentScene->update();
    for (int i = 0; i < currentScene->objects.getLength(); i++) {
        currentScene->objects.byIndex(i)->update();
    }

    for (int i = 0; i < interpolationData.size(); i++) {
        InterpolationData &data = interpolationData[i];

        bool subtract = data.target < 0;;
        
        data.decimal += (float)data.speed * getDeltaTime();

        if ((!subtract && data.decimal >= 1) || (subtract && data.decimal <= -1 )) {
            data.added += data.decimal;
            *data.reference += data.decimal;
            data.decimal -= (int)data.decimal;
        }

        if ((subtract && data.added <= data.target) || (!subtract && data.added >= data.target)) {
            *data.reference -= data.added - data.target;
            interpolationData.erase(interpolationData.begin() + i);
        }
    }
}