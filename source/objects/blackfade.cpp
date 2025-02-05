#include "../objects.hpp"

class objects::BlackFade : public objects::templates::Rect {
private:
    int alpha = 0;

public:
    void update() override {
        int display;
        if (alpha <= 0) {
            display = 0;
        }
        else if (alpha >= 255) {
            display = 255;
        }
        else {
            display = alpha;
        }

        rectangle->setSize((sf::Vector2f)window::window.getSize());
        rectangle->setFillColor({0, 0, 0, display});
    }

    void fadeOut() {
        alpha = 255;
        game::interpolationData.push_back({&alpha, -255, -500});
    }

    void fadeIn() {
        alpha = 0;
        game::interpolationData.push_back({&alpha, 255, 500});
    }

    BlackFade() : templates::Rect({0, 0}, sf::Color::Black) {
        this->zIndex = 5;
    }
};