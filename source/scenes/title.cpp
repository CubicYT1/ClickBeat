#include "../scenes.hpp"
#include "../util.hpp"

#include <iostream>

class scenes::Title : public game::Scene {
public:
    Title() {
        objects.add("logo", new objects::TitleLogo());
        objects.add("text", new objects::TitleText());

        game::music = sf::Music("assets/sound/menu.wav");
        game::music.setLooping(true);
        game::music.play();
    }

    void update() override {
    }
};