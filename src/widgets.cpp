#include "widgets.hpp"


Text::Text(std::string text_str, sf::Font& font, unsigned int font_size, sf::Color color, sf::Vector2f position)
{
    // Assign variables
    setString(text_str);
    setFontSize(font_size);
    setFont(font);
    setTextColor(color);
    setPosition(position);
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}

void Text::setString(std::string text)
{
    this->text_string = text;
    this->text.setString(text);
}

void Text::setPosition(sf::Vector2f position)
{
    this->position = position;
    this->text.setPosition(position);
}

void Text::setFontSize(unsigned int font_size)
{
    this->font_size = font_size;
    this->text.setCharacterSize(font_size);
}

void Text::setFont(sf::Font &font)
{
    this->font = font;
    this->text.setFont(font);
}

void Text::setTextColor(sf::Color color)
{
    this->text_color = color;
    this->text.setFillColor(color);
}