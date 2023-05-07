#include "widgets.hpp"

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
    /*if(this->text_string.length() == 1){
        this->text.setOrigin(getOrigin(this->text.getCharacterSize(), this->text.getCharacterSize(), origin));
    }
    else{
        this->text.setOrigin(getOrigin(getWidth(), this->text.getCharacterSize(), origin));
    }*/
    this->text.setOrigin(getOrigin(getWidth(), this->text.getCharacterSize(), origin));
}

float ui::Text::getWidth() const
{
    return this->text.getGlobalBounds().width;
}

float ui::Text::getHeight() const
{
    return this->text.getGlobalBounds().height;
}

sf::Vector2f ui::Text::getPosition() const{
    return this->position;
}

void ui::Text::updatePosition(std::pair<double, double> change_ratio, const std::shared_ptr<sf::RenderWindow>& window){
    sf::Vector2i integer_position = {(int)(this->position.x*change_ratio.first), (int)(this->position.y*change_ratio.second)};
    this->text.setPosition(window->mapPixelToCoords(integer_position, window->getView()));
    this->text.setScale(change_ratio.first, change_ratio.second);
}

ui::Button::Button(std::string text_str, sf::Font &font, unsigned int size, std::pair<sf::Color, sf::Color> background_color, std::pair<sf::Color, sf::Color> text_color, sf::Vector2f position, sf::Vector2f dimensions, ORIGIN origin){
    this->text_str = text_str;
    this->font = font;
    this->font_size = size;
    this->background_color = background_color;
    this->text_color = text_color;
    this->dimensions = dimensions;
    this->origin_coords = getOrigin(dimensions.x, dimensions.y, origin);
    this->position = position;
    this->relative_position = sf::Vector2f(position.x-origin_coords.x, position.y-origin_coords.y);
    this->clicked = true;

    shape.setSize(dimensions);
    shape.setFillColor(background_color.first);
    shape.setOrigin(origin_coords);
    shape.setPosition(position);

    this->text = std::make_unique<ui::Text>(text_str, font, font_size, text_color.first,sf::Vector2f(relative_position.x+dimensions.x/2, relative_position.y+dimensions.y/2), ui::ORIGIN::C);
}

bool ui::Button::handleInput(sf::Vector2f mouse_position, const sf::Event& e) {
    if(mouse_position.x >= relative_position.x && mouse_position.x <= relative_position.x+shape.getSize().x*shape.getScale().x && mouse_position.y >= relative_position.y && mouse_position.y <= relative_position.y+shape.getSize().y*shape.getScale().y){
        shape.setFillColor(background_color.second);
        text->setTextColor(text_color.second);
        if(e.type == sf::Event::MouseButtonReleased){
            if(e.mouseButton.button == sf::Mouse::Left){
                return true;
            }
        }
    }
    else{
        shape.setFillColor(background_color.first);
        text->setTextColor(text_color.first);
    }
    return false;
}


void ui::Button::update(sf::Vector2f mouse_position) {
    if(mouse_position.x >= relative_position.x && mouse_position.x <= relative_position.x+shape.getSize().x*shape.getScale().x && mouse_position.y >= relative_position.y && mouse_position.y <= relative_position.y+shape.getSize().y*shape.getScale().y){
        shape.setFillColor(background_color.second);
        text->setTextColor(text_color.second);
    }
    else{
        shape.setFillColor(background_color.first);
        text->setTextColor(text_color.first);
    }
}

void ui::Button::setText(const std::string &textStr) {
    text_str = textStr;
    this->text->setString(textStr);
}

void ui::Button::setPosition(const sf::Vector2f& position){
    this->position = position;
    this->relative_position = sf::Vector2f(position.x-origin_coords.x, position.y-origin_coords.y);
    shape.setPosition(position);
    text->setPosition(position);
}

void ui::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape, states);
    target.draw(*text, states);
}

const sf::Vector2f &ui::Button::getPosition() const {
    return position;
}

const sf::Vector2f &ui::Button::getRelativePosition() const {
    return relative_position;
}

const sf::Vector2f &ui::Button::getDimensions() const {
    return dimensions;
}

const std::pair<sf::Color, sf::Color> &ui::Button::getBackgroundColor() const {
    return background_color;
}

const std::pair<sf::Color, sf::Color> &ui::Button::getTextColor() const {
    return text_color;
}

const std::string &ui::Button::getTextStr() const {
    return text_str;
}

const sf::Font &ui::Button::getFont() const {
    return font;
}

unsigned int ui::Button::getFontSize() const {
    return font_size;
}

void ui::Button::updatePosition(std::pair<double, double> change_ratio, const std::shared_ptr<sf::RenderWindow>& window){
    sf::Vector2i integer_position = {(int)(this->position.x*change_ratio.first), (int)(this->position.y*change_ratio.second)};
    this->shape.setPosition(window->mapPixelToCoords(integer_position, window->getView()));
    this->text->updatePosition(change_ratio, window);
    this->relative_position = static_cast<sf::Vector2f>((window->mapPixelToCoords(integer_position, window->getView())));
    this->relative_position = {relative_position.x-(float)change_ratio.first*origin_coords.x, relative_position.y-(float)change_ratio.second*origin_coords.y};

    this->shape.setScale(change_ratio.first, change_ratio.second);
}


ui::Spinbox::Spinbox(sf::Font &font, unsigned int font_size, std::pair<sf::Color, sf::Color> background_color,
                     std::pair<sf::Color, sf::Color> text_color, sf::Vector2f position, sf::Vector2f dimensions,
                     ui::ORIGIN origin, int min_value, int max_value, int start_value) {
    this->font = font;
    this->font_size = font_size;
    this->background_color = background_color;
    this->text_color = text_color;
    this->min_value = min_value;
    this->max_value = max_value;
    this->dimensions = dimensions;
    this->origin_coords = getOrigin(dimensions.x, dimensions.y, origin);
    this->position = position;
    this->relative_position = sf::Vector2f(position.x-origin_coords.x, position.y-origin_coords.y);
    this->value = start_value;

    shape.setSize({dimensions.x-(2*dimensions.y), dimensions.y});
    shape.setFillColor(background_color.first);
    shape.setOrigin(getOrigin(shape.getSize().x, shape.getSize().y, ui::ORIGIN::C));
    shape.setPosition(sf::Vector2f(relative_position.x+dimensions.x/2, relative_position.y+dimensions.y/2));

    this->value_widget = std::make_unique<ui::Text>(std::to_string(this->value), font, font_size,text_color.first, sf::Vector2f(relative_position.x+dimensions.x/2, relative_position.y+dimensions.y/2), ui::ORIGIN::C);
    this->plus = std::make_unique<ui::Button>("+", this->font, font_size, background_color, text_color, sf::Vector2f(relative_position.x+shape.getSize().x+3*(dimensions.y/2), relative_position.y+dimensions.y/2), sf::Vector2f(dimensions.y, dimensions.y), ui::ORIGIN::C);
    this->minus = std::make_unique<ui::Button>("-", this->font, font_size, background_color, text_color, sf::Vector2f(relative_position.x+dimensions.y/2, relative_position.y+dimensions.y/2), sf::Vector2f(dimensions.y, dimensions.y), ui::ORIGIN::C);
}


int ui::Spinbox::handleInput(sf::Vector2f mouse_position, const sf::Event& e) {
    if(this->plus->handleInput(mouse_position, e)){
        if(value < max_value){
            value += 1;
        }
    }
    if(this->minus->handleInput(mouse_position, e)){
        if(value > min_value){
            value -= 1;
        }
    }
    this->value_widget->setString(std::to_string(value));
    return value;
}

void ui::Spinbox::update(sf::Vector2f mouse_position) {
    this->plus->update(mouse_position);
    this->minus->update(mouse_position);
}

void ui::Spinbox::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(shape);
    target.draw(*plus);
    target.draw(*minus);
    target.draw(*value_widget);
}

void
ui::Spinbox::updatePosition(std::pair<double, double> change_ratio, const std::shared_ptr<sf::RenderWindow> &window) {
    sf::Vector2i integer_position = {(int)(this->position.x*change_ratio.first), (int)(this->position.y*change_ratio.second)};
    this->shape.setPosition(window->mapPixelToCoords(integer_position, window->getView()));
    this->relative_position = static_cast<sf::Vector2f>((window->mapPixelToCoords(integer_position, window->getView())));
    this->relative_position = {relative_position.x-(float)change_ratio.first*origin_coords.x, relative_position.y-(float)change_ratio.second*origin_coords.y};

    this->value_widget->updatePosition(change_ratio, window);

    this->plus->updatePosition(change_ratio, window);
    this->minus->updatePosition(change_ratio, window);
    this->shape.setScale(change_ratio.first, change_ratio.second);
}
