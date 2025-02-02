#include "../objects.hpp"

#include <chrono>

class objects::BgReact : public objects::templates::Rect {
private:
public:
    void update() override {
        rectangle->setSize((sf::Vector2f)window::window.getSize());
        
        float x = game::music.timeToSamples(sf::Time(std::chrono::seconds()))
        float precent = game::music.timeToSamples() / game::music.getMaxGain();
        rectangle->setFillColor({255, 255, 255, 150.0 * precent});
    }

    BgReact() : templates::Rect({0, 0}, sf::Color::White) {}
};