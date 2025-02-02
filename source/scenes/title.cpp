#pragma once
#include "../scenes.hpp"
#include "../util.hpp"
#include "menu.cpp"

#include <iostream>

class scenes::Title : public game::Scene {
private:
    bool started = false;
    int alpha = 255;

public:
    Title() {
        objects.add("logo", new objects::TitleLogo());
        objects.add("text", new objects::TitleText());

        game::music = sf::Music("assets/sound/menu.wav");
        game::music.setLooping(true);
        game::music.play();
    }

    void update() override {
        if (alpha == 0) {
            game::currentScene = new scenes::Menu();
            delete this;
            return;
        }

        while (game::keyQueue.size()) {
            sf::Keyboard::Key key = game::keyQueue.front();

            if (key == sf::Keyboard::Key::Space && !started) {
                game::interpolationData.push_back({&alpha, -255, -500});

                objects["text"]->visible = false;
                started = true;
            }
            game::keyQueue.pop();
        }

        ((sf::Sprite*)objects["logo"]->getDrawable())->setColor({255, 255, 255, alpha});
    }
};