#include "widgets.hpp"

#include <utility>

// N, S, W, E, NW, NE, SW, SE, C

sf::Vector2f ui::getOrigin(float width, float height, ORIGIN origin)
{
    switch (origin) {
        case N:
            return {width/2, 0};
        case S:
            return {width/2, height};
        case W:
            return {0, height/2};
        case E:
            return {width, height/2};
        case NE:
            return {width, 0};
        case SW:
            return {0, height};
        case SE:
            return {width, height};
        case C:
            return {width/2, height/2};
        default:
            return {0, 0};
    }
}

ui::Text::Text(std::string text_str, sf::Font& font, unsigned int font_size, sf::Color color, sf::Vector2f position, ORIGIN origin)
{
    // Assign variables
    setString(std::move(text_str));
    setFontSize(font_size);
    setFont(font);
    setTextColor(color);
    setOrigin(origin);
    setPosition(position);
}

void ui::Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}

void ui::Text::setString(std::string text)
{
    this->text_string = text;
    this->text.setString(text);
}

void ui::Text::setPosition(sf::Vector2f position)
{
    this->position = position;
    this->text.setPosition(position);
}

void ui::Text::setFontSize(unsigned int font_size)
{
    this->font_size = font_size;
    this->text.setCharacterSize(font_size);
}

void ui::Text::setFont(sf::Font &font)
{
    this->font = font;
    this->text.setFont(font);
}

void ui::Text::setTextColor(sf::Color color)
{
    this->text_color = color;
    this->text.setFillColor(color);
}

void ui::Text::setOrigin(ORIGIN origin)
{
    this->text.setOrigin(getOrigin(getWidth(), getHeight(), origin));
}

float ui::Text::getWidth() const
{
    return this->text.getLocalBounds().width;
}

float ui::Text::getHeight() const
{
    return this->text.getLocalBounds().height;
}