#include "interface.hpp"

Interface::Interface()
{
    initVariables();
    initWindow();
}

void Interface::initVariables(){
    this->window_width = 1150;
    this->window_height = 800;
    this->font.loadFromFile("textures/mine-sweeper.ttf");
    this->window = nullptr;

    // Title initialization
    this->title = std::make_unique<ui::Text>("Minesweeper", font, 70, sf::Color(25,99,100, 255), sf::Vector2f(575, 400), ui::ORIGIN::C);
}

void Interface::initWindow(){
    this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(window_width, window_height), "Minesweeper");
}

bool Interface::isAlive() const {
    return window->isOpen();
}

void Interface::update(){
    //window->clear();
    sf::Event e;
    while(window->pollEvent(e)) {
        if (e.type == sf::Event::Closed) window->close();
    }
    window->draw(*title);
    window->display();
}
