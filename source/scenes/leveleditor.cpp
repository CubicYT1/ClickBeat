#pragma once
#include "../scenes.hpp"
#include "../util.hpp"

class scenes::LevelEditor : public game::Scene {
private:
    int bpm = 140;
    int typeIndex = 0;
    int noteCount = 0;
    
    std::vector<sf::Vector2f> notePos;
    std::vector<objects::templates::Sprite*> notes;

    std::string type = "note";
    std::string types[3] = {
        "note",
        "fakeNote",
        "obstacle"
    };

    sf::Font font = sf::Font("assets/fonts/regular.ttf");

    sf::Music scrollSfx = sf::Music("assets/sound/scroll.mp3");

    objects::templates::Text *info = new objects::templates::Text("", font);;

    objects::templates::Sprite *cursor = new objects::templates::Sprite("assets/images/note.png");

public:
    LevelEditor() {
        util::setOriginCenter(*(sf::Sprite*)cursor->getDrawable());

        objects.add("info", info);
        objects.add("cursor", cursor);

        game::music = sf::Music("assets/sound/editorbgm.mp3");
        game::music.setLooping(true);
        game::music.play();
    }

    void update() override {
        const float noteSize = window::window.getSize().x / 15;

        while (game::mouseQueue.size()) {
            const sf::Mouse::Button button = game::mouseQueue.front();

            if (button == sf::Mouse::Button::Left) {
                float xPos = (float)game::mousePosition.x / (float)window::window.getSize().x;
                float yPos = game::mousePosition.y;

                objects::templates::Sprite *note = new objects::templates::Sprite("assets/images/" + type + ".png");

                notes.push_back(note);
                notePos.push_back({xPos, yPos});

                objects.add("", note);
                noteCount++;

                std::cout << xPos;
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
            game::keyQueue.pop();
        }

        ((sf::Text*)info->getDrawable())->setString("Type: " + type + " | BPM: " + std::to_string(bpm));

        /* cursor */ {
            sf::Sprite* cursorSprite = (sf::Sprite*)cursor->getDrawable();

            const float scale = noteSize / cursorSprite->getTexture().getSize().x; 
            cursorSprite->setScale({scale, scale});
            cursorSprite->setPosition((sf::Vector2f)game::mousePosition);
            cursorSprite->setColor({255, 255, 255, 150});
        }

        for (objects::templates::Sprite *note : notes) {
            static int index = 0;

            sf::Sprite *noteSprite = (sf::Sprite*)note->getDrawable();

            float scale = noteSize / noteSprite->getTexture().getSize().x;
            noteSprite->setScale({scale, scale});

            float xPos = (float)window::window.getSize().x * notePos[index].x;
            std::cout << index << std::endl;
            noteSprite->setPosition({xPos, notePos[index].y});

            util::setOriginCenter(*noteSprite);
            index += index == notes.size() - 1 ? -index : 1;
        }
    }
};

