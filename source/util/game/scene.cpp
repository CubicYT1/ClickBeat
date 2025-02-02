#include "../game.hpp"
#include "../../util.hpp"

class game::Scene {
public:
    util::Dictionary<std::string, game::Object*> objects;

    virtual void update() {}

    ~Scene() {
        for (int i = 0; i < objects.getLength(); i++) {
            delete objects.byIndex(i);
        }
    }
};