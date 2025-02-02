#pragma once
#include "../scenes.hpp"

#include <vector>

class scenes::Menu : public game::Scene {
private:
    sf::Font songFont;
    std::vector<std::string> songs = {
        "Based Beat - ClickBeat OST",
        "Trapped Out - ClickBeat OST",
        "Amen - ClickBeat OST",
    };
    int selectedIndex = 0;
    sf::Music scrollSfx;

public:
    void ChangeMusic() {
        game::music = sf::Music("assets/sound/" + songs[selectedIndex] + ".flac");
        game::music.play();
        game::music.setLooping(true);
    }

    Menu() {
        songFont = sf::Font("assets/fonts/bold italic.ttf");
        scrollSfx = sf::Music("assets/sound/scroll.mp3");
        scrollSfx.setVolume(25);

        objects.add("songCover", new objects::SongCover());

        objects.add("line", new objects::templates::Rect({2, 2}, sf::Color::White));
        sf::RectangleShape *line = (sf::RectangleShape*)objects["line"]->getDrawable();

        objects.add("reactiveBg", new objects::BgReact());
        ((objects::BgReact*)objects["reactiveBg"])->zIndex = -1;

        for (int i = 0; i < songs.size(); i++) {
            objects.add(std::to_string(i), new objects::SongText(songs[i], songFont));
            sf::Text *text = (sf::Text*)objects[std::to_string(i)]->getDrawable();
            text->setFillColor({255, 255, 255, 100});

            if (i == 0) {
                ((objects::SongText*)objects["0"])->xOffset = 30;
                ((sf::Text*)objects["0"]->getDrawable())->setFillColor({255, 255, 255, 255});
            }
        }

        ChangeMusic();
    }

    void update() override {
        while (game::keyQueue.size()) {
            sf::Keyboard::Key key = game::keyQueue.front();
            if ((key == sf::Keyboard::Key::W && selectedIndex != 0) || (key == sf::Keyboard::Key::S && selectedIndex != songs.size() - 1)) {
                objects::SongText *previous;
                objects::SongText *current;
                bool down;

                if (key == sf::Keyboard::Key::W) {
                    previous = (objects::SongText*)objects[std::to_string(selectedIndex--)];
                    down = false;
                }
                else {
                    previous = (objects::SongText*)objects[std::to_string(selectedIndex++)];
                    down = true;
                }
                current = (objects::SongText*)objects[std::to_string(selectedIndex)];
                
                game::interpolationData.push_back({&previous->xOffset, -30, -500});
                ((sf::Text*)previous->getDrawable())->setFillColor({255, 255, 255, 100});

                game::interpolationData.push_back({&current->xOffset, 30, 500});
                ((sf::Text*)current->getDrawable())->setFillColor({255, 255, 255, 255});

                for (int i = 0; i < songs.size(); i++) {
                    objects::SongText *song = (objects::SongText*)objects[std::to_string(i)];
                    game::interpolationData.push_back({&song->yOffset, down ? -35 : 35, down ? -500 : 500});
                }

                scrollSfx.play();
                ChangeMusic();
            }
            game::keyQueue.pop();
        }

        sf::RectangleShape *line = (sf::RectangleShape*)objects["line"]->getDrawable();

        float posX = ((objects::SongCover*)objects["songCover"])->scaledSizeX + 60;
        line->setPosition({posX, 30});
        line->setSize({2, window::window.getSize().y - 60});

        for (int i = 0; i < songs.size(); i++) {
            objects::SongText* textObject = (objects::SongText*)objects[std::to_string(i)];
            sf::Text* text = (sf::Text*)textObject->getDrawable();

            int xPos = line->getPosition().x + 30 + textObject->xOffset;
            int yPos = 35 * (i + 1) + textObject->yOffset;
            text->setPosition({xPos, yPos});
        }
    }
};