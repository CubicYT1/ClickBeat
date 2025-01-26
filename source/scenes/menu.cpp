#pragma once
#include "../scenes.hpp"

class scenes::Menu : public game::Scene {
private:

public:
    Menu() {
        objects.add("songCover", new objects::SongCover());
    }

    void update() override {
     
    }
};