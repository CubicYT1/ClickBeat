#include "../scenes.hpp"

static void startMusic() {
    game::music.play();
}

class scenes::Level : public game::Scene {
private:
    int bpm;
    int failAlpha = 0;
    float yOffset = 0;
    bool started = false;
    bool fading = false;
    bool failed = false;

    std::vector<objects::Note*> notes;

    sf::Clock clock;
    sf::Clock restartDelay;

    sf::Font font = sf::Font("assets/fonts/bold italic.ttf");

    sf::Music hitSfx = sf::Music("assets/sound/noteHit.mp3");

    objects::Player *player = new objects::Player();

    objects::EventTimer *startDelay = new objects::EventTimer(util::doNothing, startMusic, 3, true);

    objects::EventTimer *menuTimer = new objects::EventTimer(util::doNothing, scenes::menu, 1.25);

    objects::EventTimer *restartTimer = new objects::EventTimer(util::doNothing, scenes::level, 1.25);

    objects::templates::Rect *redRect = new objects::templates::Rect({0, 0}, {255, 0, 0, 0});

    objects::templates::Text *failText = new objects::templates::Text("LEVEL FAILED", font);

    objects::BlackFade *fade = new objects::BlackFade();

public:
    Level(game::Song map) {
        objects.add("player", player);
        objects.add("startDelay", startDelay);
        objects.add("menutimer", menuTimer);
        objects.add("fade", fade);
        objects.add("redRect", redRect);
        objects.add("failText", failText);
        objects.add("restartTimer", restartTimer);

        redRect->zIndex = 1;
        failText->zIndex = 2;
        fade->zIndex = 3;

        game::music = sf::Music(map.getSongPath());

        fade->fadeOut();

        restartDelay.stop();

        std::string line = "";
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
    
    void levelFail() {
        if (!failed && !fading) {
            failed = true;
            game::interpolationData.push_back({&failAlpha, 125, 62});
            restartDelay.start();
        }
    }

    void update() override {
        window::window.setMouseCursorVisible(false);

        const float noteSize = window::window.getSize().x / 15;
        const float hitPoint = (float)window::window.getSize().y * 0.8;

        while (game::mouseQueue.size()) {
            const sf::Mouse::Button button = game::mouseQueue.front();

            if (button == sf::Mouse::Button::Left && !failed) {
                for (objects::Note *note : notes) { 
                    sf::Sprite noteSprite = *(sf::Sprite*)note->getDrawable();
                    sf::Sprite playerSprite = *(sf::Sprite*)player->getDrawable();

                    sf::Sprite *sprites[2] = {&noteSprite, &playerSprite};

                    for (sf::Sprite *sprite : sprites) {
                        sf::Vector2f scale = sprite->getScale();

                        scale.x /= 1.5;
                        scale.y /= 1.5;

                        sprite->setScale(scale);
                    }

                    if (noteSprite.getGlobalBounds().findIntersection(playerSprite.getGlobalBounds()) && !note->isClicked() && note->getType() != "obstacle") {
                        hitSfx.play();
                        note->click();

                        if (note->getType() == "fakeNote") {
                            levelFail();
                        }
                    }
                }
            }
        
            game::mouseQueue.pop();
        }

        while (game::keyQueue.size()) {
            sf::Keyboard::Key key = game::keyQueue.front();

            if (key == sf::Keyboard::Key::Escape && !failed && !fading) {
                fading = true;
                fade->fadeIn();
                menuTimer->start();
            }
            game::keyQueue.pop();
        }

        // note stuff
        for (objects::Note *note : notes) {
            sf::Sprite *noteSprite = (sf::Sprite*)note->getDrawable();
            
            util::setOriginCenter((sf::Sprite&)*noteSprite);

            int xPos = noteSize * note->position.x / 2;
            int yPos = noteSize * -note->position.y / 2 + yOffset * noteSize / 2 + hitPoint;
            noteSprite->setPosition({xPos, yPos});

            float scale = (float)noteSize / noteSprite->getTexture().getSize().x * (float)note->scaleMultiplier / 100;
            noteSprite->setScale({scale, scale});

            noteSprite->setColor({255, 255, 255, note->alpha});

            sf::Sprite *playerSprite = (sf::Sprite*)player->getDrawable();
            if (noteSprite->getPosition().y >= window::window.getSize().y && !note->isClicked() && note->getType() == "note") {
                levelFail();
            }
            else if (noteSprite->getGlobalBounds().findIntersection(playerSprite->getGlobalBounds()) && !note->isClicked() && note->getType() == "obstacle") {
                levelFail();

                note->click();
            }
        }

        /* offset */ {
            float affector = clock.getElapsedTime().asSeconds() - 3;

            if (game::music.getStatus() == sf::SoundSource::Status::Playing) {
                affector = game::music.getPlayingOffset().asSeconds();
                started = true;
                clock.reset();
            }
            else if (!fading && started && game::music.getStatus() == sf::SoundSource::Status::Stopped && !failed) {
                fading = true;
                menuTimer->start();
                fade->fadeIn();
            }

            yOffset = affector * bpm / 60 * 8;
        }

        /* fail Visuals */ {
            sf::RectangleShape *rect = (sf::RectangleShape*)redRect->getDrawable();
            sf::Text *text = (sf::Text*)failText->getDrawable();

            text->setCharacterSize(50);
            text->setOrigin(text->getLocalBounds().getCenter());
            text->setPosition(window::window.getView().getCenter());
            text->setFillColor({255, 255, 255, failAlpha});

            rect->setSize((sf::Vector2f)window::window.getSize());
            rect->setFillColor({250, 0, 0, failAlpha});
        }

        if (failed) {
            game::music.setPitch(game::music.getPitch() - 0.5 * game::getDeltaTime());

            if (restartDelay.getElapsedTime().asSeconds() >= 1.75 && restartDelay.isRunning()) {
                restartTimer->start();
                fade->fadeIn();
                restartDelay.stop();
            }  
        }
        else if (fading) {
            game::music.setPitch(game::music.getPitch() - 1 * game::getDeltaTime());
        }
    }
};