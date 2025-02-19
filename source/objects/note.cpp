#include "../objects.hpp"

class objects::Note : public objects::templates::Sprite {
private:
    std::string type;
    
    bool clicked = false;

public:
    sf::Vector2i position;

    int scaleMultiplier = 100;
    int alpha = 255;

    Note(std::string type) : templates::Sprite("assets/images/" + type + ".png") {
        this->type = type;
    }

    void update() override {
        this->visible = !(alpha <= 0);
    }

    std::string getType() {
        return type;
    }

    bool isClicked() {
        return clicked;
    }

    void click() {
        clicked = true;
        game::interpolationData.push_back({&scaleMultiplier, 300, 500});
        game::interpolationData.push_back({&alpha, -255, -450});
    }
};