#pragma once
#include "../scenes.hpp"
#include "../util.hpp"
#include "../objects.hpp"

#include <fstream>

class scenes::LevelEditor : public game::Scene {
private:
    int bpm = 140;
    int typeIndex = 0;
    int cursorXPos = 0;
    int cursorYPos = 0;

    bool preview = false;

    float yOffset = 0;
    int lastY = -1;

    std::vector<sf::Vector2i> notePos;
    std::vector<objects::templates::Sprite*> notes;
    std::vector<std::string> noteTypes;

    std::string type = "note";
    std::string types[3] = {
        "note",
        "fakeNote",
        "obstacle"
    };

    game::Song map;

    sf::Font font = sf::Font("assets/fonts/regular.ttf");

    sf::Music scrollSfx = sf::Music("assets/sound/scroll.mp3");
    sf::Music beatSfx = sf::Music("assets/sound/beat.mp3");

    sf::Clock clock;

    objects::templates::Text *info = new objects::templates::Text("", font);;

    objects::templates::Sprite *cursor = new objects::templates::Sprite("assets/images/note.png");

    objects::templates::Rect *line = new objects::templates::Rect({window::window.getSize().x, 2}, sf::Color::White);

public:
    LevelEditor(game::Song map) : map(map) {
        util::setOriginCenter(*(sf::Sprite*)cursor->getDrawable());
        line->zIndex = 1;

        objects.add("info", info);
        objects.add("cursor", cursor);
        objects.add("line", line);

        game::music = sf::Music("assets/sound/editorbgm.mp3");
        game::music.setLooping(true);
        game::music.play();

        std::string line;
        std::ifstream reader;
        reader.open(map.getMapPath());

        std::getline(reader, line);

        if (line == "") {
            reader.close();
            return;
        }

        bpm = std::stoi(line);
        std::getline(reader, line);

        while (!reader.eof()) {
            std::getline(reader, line);
            objects::templates::Sprite *note = new objects::templates::Sprite("assets/images/" + line + ".png");
            sf::Vector2i pos;

            noteTypes.push_back(line);

            std::getline(reader, line);
            pos.x = std::stoi(line);

            std::getline(reader, line);
            pos.y = std::stoi(line);

            notes.push_back(note);
            notePos.push_back(pos);
            objects.add("", note);
        }
        reader.close();

        beatSfx.setVolume(50);
    }

    void update() override {
        const float noteSize = window::window.getSize().x / 15;

        while (game::mouseQueue.size()) {
            const sf::Mouse::Button button = game::mouseQueue.front();

            if (button == sf::Mouse::Button::Left && !preview) {
                bool deleted = false;

                int index = 0;
                for (sf::Vector2i note : notePos) {
                    if (note.x == cursorXPos && note.y == cursorYPos) {
                        notes[index]->zIndex = -1;

                        for (int i = 0; i < objects.getLength(); i++) {
                            if (objects.byIndex(i)->zIndex == -1) {
                                objects.remove(i);
                                deleted = true;
                                break;
                            }
                        }

                        notePos.erase(notePos.begin() + index);
                        notes.erase(notes.begin() + index);
                        noteTypes.erase(noteTypes.begin() + index);
                    }

                    index++;
                }

                if (!deleted) {
                    objects::templates::Sprite *note = new objects::templates::Sprite("assets/images/" + type + ".png");

                    notes.push_back(note);
                    notePos.push_back({cursorXPos, cursorYPos});
                    noteTypes.push_back(type);

                    objects.add("", note); 
                }
            }

            game::mouseQueue.pop();
        }

        while (game::keyQueue.size()) {
            const sf::Keyboard::Key key = game::keyQueue.front();

            if (key == sf::Keyboard::Key::Q || key == sf::Keyboard::Key::E) {
                if (key == sf::Keyboard::Key::Q) {
                    typeIndex += typeIndex == 0 ? sizeof(types) / sizeof(std::string) - 1 : -1;
                }
                else {
                    typeIndex += typeIndex == sizeof(types) / sizeof(std::string) - 1 ? -typeIndex : 1;
                }

                type = types[typeIndex];
                cursor->changeTexture("assets/images/" + type + ".png");
                scrollSfx.play();
            }
            else if (key == sf::Keyboard::Key::A || key == sf::Keyboard::Key::D) {
                if (key == sf::Keyboard::Key::A) {
                    cursorXPos += cursorXPos == 0 ? 30 : -1; 
                }
                else {
                    cursorXPos += cursorXPos == 30 ? -30: 1; 
                }
            }
            else if (key == sf::Keyboard::Key::W || key == sf::Keyboard::Key::S) {
                if (key == sf::Keyboard::Key::W) {
                    cursorYPos++;
                }
                else if (cursorYPos > 0) {
                    cursorYPos--;
                }
            }
            else if (key == sf::Keyboard::Key::R || key == sf::Keyboard::Key::F) {
                if (key == sf::Keyboard::Key::R) {
                    bpm++;
                }
                else {
                    bpm--;
                }
            }
            else if (key == sf::Keyboard::Key::Escape) {
                int noteCount = 0;
                for (std::string string : noteTypes) {
                    if (string == "note") {
                        noteCount++;
                    }
                }

                std::ofstream writer;
                writer.open(map.getMapPath());

                writer << std::to_string(bpm);
                writer << std::endl << std::to_string(noteCount);

                for (int i = 0; i < notes.size(); i++) {
                    writer << std::endl << noteTypes[i];
                    writer << std::endl << std::to_string(notePos[i].x);
                    writer << std::endl << std::to_string(notePos[i].y);
                }
                writer.close();

                scenes::menu();
            }
            else if (key == sf::Keyboard::Key::Space) {
                preview = !preview;

                game::music = sf::Music(preview ? map.getSongPath() : "assets/sound/editorbgm.mp3");
                game::music.setLooping(true);
                game::music.play();

                if (!preview) {
                    lastY = -1;

                    for (objects::templates::Sprite *note : notes) {
                        note->visible = true;
                    }
                }
                else {
                    float totalBeats = (float)bpm / 60 * game::music.getDuration().asSeconds();
                    std::cout << totalBeats;
                    game::music.setPlayingOffset(sf::seconds(game::music.getDuration().asSeconds() * ((float)cursorYPos / totalBeats) / 8));
                    yOffset = cursorYPos;
                }

                clock.restart();
            }

            game::keyQueue.pop();
        }

        ((sf::Text*)info->getDrawable())->setString("Type: " + type + " | BPM: " + std::to_string(bpm));

        /* cursor */ {
            sf::Sprite* cursorSprite = (sf::Sprite*)cursor->getDrawable();

            const float scale = noteSize / cursorSprite->getTexture().getSize().x; 
            cursorSprite->setScale({scale, scale});
            cursorSprite->setPosition({cursorXPos * noteSize / 2, window::window.getSize().y / 2});
            cursorSprite->setColor({255, 255, 255, 150});
        }

        /* line */ {
            sf::RectangleShape *lineShape = (sf::RectangleShape*)line->getDrawable();
            lineShape->setPosition({0, window::window.getSize().y / 2});
            lineShape->setSize({window::window.getSize().x, 2});
        }

        for (objects::templates::Sprite *note : notes) {
            static int index = 0;

            sf::Sprite *noteSprite = (sf::Sprite*)note->getDrawable();

            float scale = noteSize / noteSprite->getTexture().getSize().x;
            noteSprite->setScale({scale, scale});

            util::setOriginCenter(*noteSprite);

            int xPos = notePos[index].x * noteSize / 2;
            int yPos = window::window.getSize().y / 2 - notePos[index].y * noteSize / 2;
            yPos += noteSize * (preview ? yOffset : cursorYPos) / 2;

            noteSprite->setPosition({xPos, yPos});
            index += index == notes.size() - 1 ? -index : 1;
        }

        if (preview) {
            yOffset = game::music.getPlayingOffset().asSeconds() * bpm / 60 * 8;

            if ((int)yOffset > lastY) {
                lastY = yOffset;

                for (int i = 0; i < notes.size(); i++) {
                    if (notePos[i].y == (int)yOffset && noteTypes[i] == "note") {
                        beatSfx.play();
                        notes[i]->visible = false;
                    }
                }
            }
        }
    }
};

