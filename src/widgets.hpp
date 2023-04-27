#ifndef WIDGETS_HPP
#define WIDGETS_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include <string>

namespace ui{
    typedef enum{N, S, W, E, NW, NE, SW, SE, C} ORIGIN;

    sf::Vector2f getOrigin(float width, float height, ORIGIN origin);

    class Text;
}

class ui::Text: public sf::Drawable {
private:
    unsigned int font_size;
    std::string text_string;
    sf::Color text_color;
    sf::Font font;
    sf::Vector2f position;
    sf::Text text;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    void setFontSize(unsigned int size);

    void setPosition(sf::Vector2f position);

    void setTextColor(sf::Color color);

    void setFont(sf::Font &font);

    void setString(std::string text);

    void setOrigin(ORIGIN origin);

    float getWidth() const;

    float getHeight() const;

    Text(std::string text_str, sf::Font &font, unsigned int size, sf::Color color, sf::Vector2f position,
         ORIGIN origin = NW);

};
#endif