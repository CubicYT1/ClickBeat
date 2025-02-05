#include "../objects.hpp"

class objects::BgFlash : public objects::templates::Rect {
private:
    int alpha = 0;

public:
    void update() override {
        rectangle->setSize((sf::Vector2f)window::window.getSize());
        rectangle->setFillColor({255, 255, 255, alpha <= 0 ? 0 : alpha});
    }

    void flash() {
        alpha = 175;
        game::interpolationData.push_back({&alpha, -255, -250});
    }

    BgFlash() : templates::Rect({0, 0}, sf::Color::White) {
        this->zIndex = -1;
    }
};