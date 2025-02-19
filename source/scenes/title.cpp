#pragma once
#include "../scenes.hpp"
#include "../util.hpp"
#include "../objects.hpp"

#include <iostream>



class scenes::Title : public game::Scene {
private:
    bool started = false;
    int alpha = 255;

    objects::BlackFade *fade = new objects::BlackFade();

    objects::EventTimer *menuTimer = new objects::EventTimer(util::doNothing, scenes::menu, 1.25);

public:
    Title() {
        objects.add("logo", new objects::TitleLogo());
        objects.add("text", new objects::TitleText());
        objects.add("flash", new objects::BgFlash());
        objects.add("fade", fade);
        objects.add("menutimer", menuTimer);

        ((objects::BlackFade*)objects["fade"])->fadeOut();

        game::music = sf::Music("assets/sound/menu.wav");
        game::music.setLooping(true);
        game::music.play();
    }

    void update() override {
        while (game::keyQueue.size()) {
            sf::Keyboard::Key key = game::keyQueue.front();

            if (key == sf::Keyboard::Key::Space && !started) {
                ((objects::BgFlash*)objects["flash"])->flash();

                objects["text"]->visible = false;
                started = true;
                fade->fadeIn();
                menuTimer->start();
            }
            game::keyQueue.pop();
        }

        while (game::mouseQueue.size()) {
            game::mouseQueue.pop();
        }

        ((sf::Sprite*)objects["logo"]->getDrawable())->setColor({255, 255, 255, alpha});
    }
};