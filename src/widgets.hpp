#ifndef WIDGETS_HPP
#define WIDGETS_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include <string>


class Text: public sf::Drawable
{
private:
    unsigned int font_size;
    std::string text_string;
    sf::Color text_color;
    sf::Font font;
    sf::Vector2f position;
    sf::Text text;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    void setFontSize(unsigned int size);
    void setPosition(sf::Vector2f position);
    void setTextColor(sf::Color color);
    void setFont(sf::Font &font);
    void setString(std::string text);
    Text(std::string text_str, sf::Font& font, unsigned int size, sf::Color color, sf::Vector2f position);
};



#endif