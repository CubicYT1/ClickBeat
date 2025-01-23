#include "../scenes.hpp"
#include "../util.hpp"

#include <iostream>

class scenes::Title : public game::Scene {
public:
    void update() override {
    }

    Title() {
        objects.add("logo", new objects::TitleLogo());
    }
};