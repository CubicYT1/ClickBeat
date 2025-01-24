#include "../scenes.hpp"
#include "../util.hpp"

#include <iostream>

class scenes::Title : public game::Scene {
private:
    bool started = false;
    float alpha = 255;

public:
    Title() {
        objects.add("logo", new objects::TitleLogo());
        objects.add("text", new objects::TitleText());

        game::music = sf::Music("assets/sound/menu.wav");
        game::music.setLooping(true);
        game::music.play();
    }

    void update() override {
        while (game::keyQueue.size()) {
            sf::Keyboard::Key key = game::keyQueue.front();
            if (key == sf::Keyboard::Key::Space && !started) {
                objects["text"]->visible = false;
                started = true;
            }
            game::keyQueue.pop();
        }

        if (started) {
            alpha -= 500.0 * game::getDeltaTime();
            ((sf::Sprite*)objects["logo"]->getDrawable())->setColor({255, 255, 255, alpha});;
        }
    }
};