#pragma once
#include "../scenes.hpp"

#include <vector>

class scenes::Menu : public game::Scene {
private:
    sf::Font songFont;
    std::vector<game::Song> songs;
    int selectedIndex = 0;
    sf::Music scrollSfx;

public:
    void ChangeSong() {
        game::music = sf::Music(songs[selectedIndex].getSongPath());
        game::music.play();
        game::music.setLooping(true);

        ((objects::SongCover*)objects["songCover"])->change(songs[selectedIndex].getCoverPath());
    }

    Menu() {
        songs = game::getSongs();

        songFont = sf::Font("assets/fonts/bold italic.ttf");
        scrollSfx = sf::Music("assets/sound/scroll.mp3");
        scrollSfx.setVolume(25);

        objects.add("songCover", new objects::SongCover());
        objects.add("line", new objects::templates::Rect({2, 2}, sf::Color::White));
        objects.add("flash", new objects::BgFlash());
        objects.add("fade", new objects::BlackFade());
        objects.add("duration", new objects::templates::Text("00:00", songFont)); 

        sf::RectangleShape *line = (sf::RectangleShape*)objects["line"]->getDrawable();
        ((objects::BlackFade*)objects["fade"])->fadeOut();

        sf::Text *duration = (sf::Text*)objects["duration"]->getDrawable();
        duration->setCharacterSize(20);
        duration->setOutlineThickness(2);

        for (int i = 0; i < songs.size(); i++) {
            objects.add(std::to_string(i), new objects::SongText(songs[i].getName(), songFont));
            sf::Text *text = (sf::Text*)objects[std::to_string(i)]->getDrawable();
            text->setFillColor({255, 255, 255, 100});

            if (i == 0) {
                ((objects::SongText*)objects["0"])->xOffset = 30;
                ((sf::Text*)objects["0"]->getDrawable())->setFillColor({255, 255, 255, 255});
            }
        }

        ChangeSong();
    }

    void update() override {
        while (game::keyQueue.size()) {
            const sf::Keyboard::Key key = game::keyQueue.front();

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
                ((objects::BgFlash*)objects["flash"])->flash();
                ChangeSong();
            }
            else if (key == sf::Keyboard::Key::F12) {
                game::currentScene = new scenes::LevelEditor();
                delete this;
                return;
            }

            game::keyQueue.pop();
        }

        while (game::mouseQueue.size()) {
            game::mouseQueue.pop();
        }

        objects::SongCover *songCover = (objects::SongCover*)objects["songCover"];
        
        sf::RectangleShape *line = (sf::RectangleShape*)objects["line"]->getDrawable();
        line->setPosition({songCover->scaledSizeX + 60, 30});
        line->setSize({2, window::window.getSize().y - 60});  
        
        {
            sf::Text *duration = (sf::Text*)objects["duration"]->getDrawable();
            duration->setOrigin({duration->getLocalBounds().size.x / 2, duration->getLocalBounds().size.y / 2});
            duration->setPosition({songCover->scaledSizeX / 2 + 30, songCover->scaledSizeY + 26});  

            int seconds = game::music.getDuration().asSeconds();
            int minutes = seconds / 60;
            seconds -= 60 * minutes;

            duration->setString(std::to_string(minutes) + ":" + std::to_string(seconds));
        }
        
        for (int i = 0; i < songs.size(); i++) {
            objects::SongText* textObject = (objects::SongText*)objects[std::to_string(i)];
            sf::Text* text = (sf::Text*)textObject->getDrawable();

            int xPos = line->getPosition().x + 30 + textObject->xOffset;
            int yPos = 35 * (i + 1) + textObject->yOffset;
            text->setPosition({xPos, yPos});
        }
    }
};