#pragma once
#include "../scenes.hpp"
#include "../util.hpp"
#include "menu.cpp"

#include <iostream>

class scenes::Title : public game::Scene {
private:
    bool started = false;
    int alpha = 255;
    sf::Clock clock;

public:
    Title() {
        objects.add("logo", new objects::TitleLogo());
        objects.add("text", new objects::TitleText());
        objects.add("flash", new objects::BgFlash());
        objects.add("fade", new objects::BlackFade());

        clock.reset();

        game::music = sf::Music("assets/sound/menu.wav");
        game::music.setLooping(true);
        game::music.play();
    }

    void update() override {
        if (clock.getElapsedTime().asSeconds() >= 1) {
            game::currentScene = new scenes::Menu();
            delete this;
        }

        while (game::keyQueue.size()) {
            sf::Keyboard::Key key = game::keyQueue.front();

            if (key == sf::Keyboard::Key::Space && !started) {
                ((objects::BgFlash*)objects["flash"])->flash();
                ((objects::BlackFade*)objects["fade"])->fadeIn();

                objects["text"]->visible = false;
                clock.start();
                started = true;
            }
            game::keyQueue.pop();
        }

        while (game::mouseQueue.size()) {
            game::mouseQueue.pop();
        }

        ((sf::Sprite*)objects["logo"]->getDrawable())->setColor({255, 255, 255, alpha});
    }
};