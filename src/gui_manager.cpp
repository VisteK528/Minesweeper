//
// Created by piotr on 5/3/23.
//

#include "gui_manager.hpp"

GuiManager::GuiManager(sf::Font &font, std::pair<sf::Color, sf::Color> widget_default_background_color,
                       std::pair<sf::Color, sf::Color> widget_default_text_color) {
    this->font = font;
    this->background_colors = widget_default_background_color;
    this->text_colors = widget_default_text_color;
}

std::unique_ptr<ui::Text> GuiManager::createText(std::string text, unsigned int font_size, sf::Vector2f position,
                                                 sf::Color color, ui::ORIGIN origin){
    return std::make_unique<ui::Text>(text, this->font, font_size, color, position, origin);
}
std::unique_ptr<ui::Text> GuiManager::createText(std::string text, unsigned int font_size, sf::Vector2f position, ui::ORIGIN origin){
    return createText(text, font_size, position, text_colors.first, origin);
}

std::unique_ptr<ui::Button> GuiManager::createButton(std::string text, unsigned int font_size, sf::Vector2f position,
                                       sf::Vector2f dimensions, std::pair<sf::Color, sf::Color> background_color,
                                       std::pair<sf::Color, sf::Color> text_color, ui::ORIGIN origin){
    return std::make_unique<ui::Button>(text, this->font, font_size, background_color, text_color,
                                        position, dimensions, origin);
}
std::unique_ptr<ui::Button> GuiManager::createButton(std::string text, unsigned int font_size, sf::Vector2f position,
                                                     sf::Vector2f dimensions, ui::ORIGIN origin){
    return createButton(text, font_size, position, dimensions, this->background_colors, this->text_colors, origin);
}

std::unique_ptr<ui::Spinbox> GuiManager::createSpinbox(unsigned int font_size, sf::Vector2f position, sf::Vector2f dimensions,
                                           std::pair<sf::Color,sf::Color> background_color,
                                           std::pair<sf::Color, sf::Color> text_color,
                                           int min_value, int max_value, int start_value,
                                           ui::ORIGIN origin){
    return std::make_unique<ui::Spinbox>(this->font, font_size, background_color, text_color, position,
                                         dimensions, origin, min_value, max_value, start_value);
}

std::unique_ptr<ui::Spinbox> GuiManager::createSpinbox(unsigned int font_size, sf::Vector2f position, sf::Vector2f dimensions,
                                                       int min_value, int max_value, int start_value,
                                                       ui::ORIGIN origin){
    return createSpinbox(font_size, position, dimensions, this->background_colors, this->text_colors, min_value, max_value, start_value, origin);
}