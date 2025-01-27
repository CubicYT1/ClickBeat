#pragma once
#include "../scenes.hpp"

class scenes::Menu : public game::Scene {
private:

public:
    Menu() {
        objects.add("songCover", new objects::SongCover());
        objects.add("line", new objects::templates::Rect({2, 2}, sf::Color::White));
    }

    void update() override {
        {
            sf::RectangleShape *line = (sf::RectangleShape*)objects["line"]->getDrawable();

            float posX = ((objects::SongCover*)objects["songCover"])->scaledSizeX + 60;
            line->setPosition({posX, 30});
            line->setSize({2, window::window.getSize().y - 60});
        }


    }
};