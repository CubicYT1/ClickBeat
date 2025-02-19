#include "../objects.hpp"

class objects::EventTimer : public game::Object {
private:
    void (*onStart)();
    void (*onFinish)();

    float seconds;

    sf::Clock clock;

public:
    EventTimer(void (*onStart)(), void (*onFinish)(), float seconds, bool autoStart = false) {
        this->onStart = onStart;
        this->onFinish = onFinish;
        this->seconds = seconds;

        clock.stop();

        if (autoStart) {
            clock.start();
            onStart();
        }
    }

    void update() override {
        if (clock.isRunning() && clock.getElapsedTime().asSeconds() >= seconds) {
            clock.stop();
            onFinish();
        }
    }

    void start() {
        clock.reset();
        clock.start();
        onStart();
    }
};