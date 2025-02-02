#include "../objects.hpp"

class objects::SongText : public objects::templates::Text {
private:
public:
    int xOffset = 0;
    int yOffset = 0;

    SongText(const std::string text, const sf::Font &font) : templates::Text(text, font) {}
};