#pragma once
#include "../scenes.hpp"
#include "../util.hpp"
#include "../objects.hpp"

#include <vector>

class scenes::Menu : public game::Scene {
private:
    int selectedIndex = 0;

    bool fading = false;

    std::string fileData;

    std::vector<game::Song> songs;

    sf::Font songFont = sf::Font("assets/fonts/bold italic.ttf");
    
    sf::Music scrollSfx = sf::Music("assets/sound/scroll.mp3");

    objects::BlackFade *fade = new objects::BlackFade();

    objects::EventTimer *titleTimer = new objects::EventTimer(util::doNothing, scenes::title, 1.25);
    objects::EventTimer *editorTimer = new objects::EventTimer(util::doNothing, scenes::editor, 1.25);
    objects::EventTimer *levelTimer = new objects::EventTimer(util::doNothing, scenes::level, 1.25);

    objects::templates::Rect *bgRect = new objects::templates::Rect({0, 0}, sf::Color(0, 0, 0, 150));

public:
    void ChangeSong() {
        game::music = sf::Music(songs[selectedIndex].getSongPath());
        game::music.play();
        game::music.setLooping(true);

        ((objects::SongCover*)objects["songCover"])->change(songs[selectedIndex].getCoverPath());

        std::string line = "";
        std::ifstream reader;
        reader.open(songs[selectedIndex].getMapPath());

        std::getline(reader, line);

        if (line == "") {
            fileData = "\n\nBPM: N/A\n\nNOTES: N/A\n\nNPS: N/A";
            return;
        }

        fileData = "\n\nBPM: " + line;

        std::getline(reader, line);
        fileData += "\n\nNOTES: " + line + "\n\nNPS: " + std::to_string(std::stoi(line) / (int)game::music.getDuration().asSeconds());
    }

    Menu() {
        songs = game::getSongs();

        scrollSfx.setVolume(25);

        objects.add("songCover", new objects::SongCover());
        objects.add("line", new objects::templates::Rect({2, 2}, sf::Color::White));
        objects.add("flash", new objects::BgFlash());
        objects.add("fade", fade);
        objects.add("duration", new objects::templates::Text("00:00", songFont)); 
        objects.add("titletimer", titleTimer);
        objects.add("editortimer", editorTimer);
        objects.add("levektimer", levelTimer);
        objects.add("bgRect", bgRect);

        bgRect->zIndex = -1;

        sf::RectangleShape *line = (sf::RectangleShape*)objects["line"]->getDrawable();
        fade->fadeOut();

        sf::Text *duration = (sf::Text*)objects["duration"]->getDrawable();
        duration->setCharacterSize(20);

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
        window::window.setMouseCursorVisible(true);

        while (game::keyQueue.size()) {
            const sf::Keyboard::Key key = game::keyQueue.front();

            if ((key == sf::Keyboard::Key::W && selectedIndex != 0) || (key == sf::Keyboard::Key::S && selectedIndex != songs.size() - 1) && !fading) {
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
            else if (key == sf::Keyboard::Key::F12 && !fading) {
                fade->fadeIn();
                editorTimer->start();
                fading = true;
            }
            else if (key == sf::Keyboard::Key::Escape && !fading) {
                fade->fadeIn();
                titleTimer->start();
                fading = true;
            }
            else if (key == sf::Keyboard::Key::Space && !fading) {
                fade->fadeIn();
                levelTimer->start();

                fading = true;
            }

            game::keyQueue.pop();
        }

        while (game::mouseQueue.size()) {
            game::mouseQueue.pop();
        }

        objects::SongCover *songCover = (objects::SongCover*)objects["songCover"];
        
        sf::RectangleShape *line = (sf::RectangleShape*)objects["line"]->getDrawable();
        line->setPosition({songCover->scaledSizeX + 60, 0});
        line->setSize({2, window::window.getSize().y});  

        ((sf::RectangleShape*)bgRect->getDrawable())->setSize({songCover->scaledSizeX + 60, window::window.getSize().y});
        
        {
            sf::Text *duration = (sf::Text*)objects["duration"]->getDrawable();
            float scale = (float)songCover->scaledSizeX / duration->getLocalBounds().size.x * 0.9;

            duration->setScale({scale, scale});
            duration->setOrigin({duration->getLocalBounds().size.x / 2, 0});
            duration->setPosition({songCover->scaledSizeX / 2 + 30, songCover->scaledSizeY + 60});  
            duration->setCharacterSize(40);

            int seconds = game::music.getDuration().asSeconds();
            int minutes = seconds / 60;
            seconds -= 60 * minutes;

            duration->setString("LENGTH: " + std::to_string(minutes) + ":" + std::to_string(seconds) + fileData);
        }
        
        for (int i = 0; i < songs.size(); i++) {
            objects::SongText* textObject = (objects::SongText*)objects[std::to_string(i)];
            sf::Text* text = (sf::Text*)textObject->getDrawable();

            int xPos = line->getPosition().x + 30 + textObject->xOffset;
            int yPos = 35 * (i + 1) + textObject->yOffset;
            text->setPosition({xPos, yPos});
        }

        if (fading) {
            game::music.setPitch(game::music.getPitch() - 1.0 * game::getDeltaTime());
        }

        delete game::mapToLoad;
        game::mapToLoad = new game::Song(songs[selectedIndex].getName());
    }
};