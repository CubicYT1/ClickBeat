#include "../../objects.hpp"

class objects::templates::Text : public game::Object {
private:
    sf::Text *text;
public:
    Text(const std::string text, const sf::Font &font) {
        this->text = new sf::Text(font, text);
    }

    ~Text() {
        delete text;
    }

    sf::Drawable *getDrawable() override {
        return text;
    }
};