//
// Created by piotr on 4/29/23.
//

#include "menu.hpp"

Menu::Menu(std::shared_ptr<sf::RenderWindow> window, sf::Font& font): State(window) {
    this->title = nullptr;
    this->start = nullptr;
    this->exit = nullptr;
    this->font = font;
    initVariables();
}

void Menu::initVariables() {
    std::pair<sf::Color, sf::Color> background_color = {sf::Color::Black, sf::Color::Black};
    std::pair<sf::Color, sf::Color> text_color = {sf::Color::White, sf::Color::Red};


    this->title = std::make_unique<ui::Text>("Minesweeper", font, 70, sf::Color(25,99,100, 255), sf::Vector2f(575, 300), ui::ORIGIN::C);
    this->start = std::make_unique<ui::Button>("> Start", this->font, 20, background_color, text_color, sf::Vector2f(575, 450), sf::Vector2f(200, 50), ui::ORIGIN::C);
    this->exit = std::make_unique<ui::Button>("> Exit", this->font, 20, background_color, text_color, sf::Vector2f(575, 550), sf::Vector2f(200, 50), ui::ORIGIN::C);
}

void Menu::updateKeybinds(){
    this->checkForQuit();
}

void Menu::update(){
    sf::Vector2i position = sf::Mouse::getPosition(*this->window);

    this->start->update(static_cast<sf::Vector2f>(position));
    this->exit->update(static_cast<sf::Vector2f>(position));
}

void Menu::render(std::shared_ptr<sf::RenderTarget> target){
    target->draw(*this->title);
    target->draw(*this->start);
    target->draw(*this->exit);

}