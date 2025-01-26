#include "../game.hpp"

#include <iostream>
#include <algorithm>

void game::update() {
    currentScene->update();
    for (int i = 0; i < currentScene->objects.getLength(); i++) {
        currentScene->objects.byindex(i)->update();
    }

    for (int i = 0; i < interpolationData.size(); i++) {
        InterpolationData &data = interpolationData[i];

        bool subtract = data.value > data.target;
        data.value += (subtract ? (float)-data.speed : (float)data.speed) * getDeltaTime();

        if ((subtract && data.value <= data.target) || (!subtract && data.value >= data.target)) {
            *data.reference = data.target;
            interpolationData.erase(interpolationData.begin() + i);
        }
        else {
            *data.reference = data.value;
        }
    }
}