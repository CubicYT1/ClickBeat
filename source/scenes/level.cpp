#include "../scenes.hpp"

static void startMusic() {
    game::music.play();
}

class scenes::Level : public game::Scene {
private:
    int bpm;
    float yOffset = 0;
    bool started = false;
    bool fading = false;

    std::vector<objects::Note*> notes;

    sf::Clock clock;

    sf::Music hitSfx = sf::Music("assets/sound/noteHit.mp3");

    objects::Player *player = new objects::Player();

    objects::EventTimer *startDelay = new objects::EventTimer(util::doNothing, startMusic, 3, true);

    objects::EventTimer *menuTimer = new objects::EventTimer(util::doNothing, scenes::menu, 1.25);

    objects::BlackFade *fade = new objects::BlackFade();

public:
    Level(game::Song map) {
        objects.add("player", player);
        objects.add("startDelay", startDelay);
        objects.add("menutimer", menuTimer);
        objects.add("fade", fade);

        game::music = sf::Music(map.getSongPath());

        fade->fadeOut();

        std::string line;
        std::ifstream reader;
        reader.open(map.getMapPath());

        std::getline(reader, line);

        if (line == "") {
            reader.close();
            scenes::menu();
        }

        bpm = std::stoi(line);
        std::getline(reader, line);

        while (!reader.eof()) {
            std::getline(reader, line);
            objects::Note *note = new objects::Note(line);

            std::getline(reader, line);
            note->position.x = std::stoi(line);

            std::getline(reader, line);
            note->position.y = std::stoi(line);

            notes.push_back(note);
            objects.add("", note);
        }
        reader.close();

        yOffset = -((float)bpm / 60 * 3);
    }

    void update() override {
        window::window.setMouseCursorVisible(false);

        const float noteSize = window::window.getSize().x / 15;
        const float hitPoint = (float)window::window.getSize().y * 0.8;

        while (game::mouseQueue.size()) {
            const sf::Mouse::Button button = game::mouseQueue.front();

            if (button == sf::Mouse::Button::Left) {
                for (objects::Note *note : notes) { 
                    sf::Sprite noteSprite = *(sf::Sprite*)note->getDrawable();
                    sf::Sprite playerSprite = *(sf::Sprite*)player->getDrawable();

                    sf::Sprite *sprites[2] = {&noteSprite, &playerSprite};

                    for (sf::Sprite *sprite : sprites) {
                        sf::Vector2f scale = sprite->getScale();

                        scale.x /= 1.6;
                        scale.y /= 1.6;

                        sprite->setScale(scale);
                    }

                    if (noteSprite.getGlobalBounds().findIntersection(playerSprite.getGlobalBounds())) {
                        hitSfx.play();
                        note->click();
                    }
                }
            }
        
            game::mouseQueue.pop();
        }

        for (objects::Note *note : notes) {
            sf::Sprite *noteSprite = (sf::Sprite*)note->getDrawable();
            
            util::setOriginCenter((sf::Sprite&)*noteSprite);

            int xPos = noteSize * note->position.x / 2;
            int yPos = noteSize * -note->position.y / 2 + yOffset * noteSize / 2 + hitPoint;
            noteSprite->setPosition({xPos, yPos});

            float scale = (float)noteSize / noteSprite->getTexture().getSize().x * (float)note->scaleMultiplier / 100;
            noteSprite->setScale({scale, scale});

            noteSprite->setColor({255, 255, 255, note->alpha});
        }

        /* offset */ {
            float affector = clock.getElapsedTime().asSeconds() - 3;

            if (game::music.getStatus() == sf::SoundSource::Status::Playing) {
                affector = game::music.getPlayingOffset().asSeconds();
                started = true;
                clock.reset();
            }
            else if (!fading && started && game::music.getStatus() == sf::SoundSource::Status::Stopped) {
                fading = true;
                menuTimer->start();
                fade->fadeIn();
            }

            yOffset = affector * bpm / 60 * 8;
        }
    }
};