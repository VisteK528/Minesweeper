#include "menu.hpp"

Menu::Menu(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, sf::Font& font): State(window, states) {
    this->title = nullptr;
    this->start = nullptr;
    this->exit = nullptr;
    this->font = font;
    initVariables();
}

void Menu::initVariables() {
    this->background.loadFromFile("textures/menu_background.png");
    this->background_texture.loadFromImage(background);

    this->background_rectangle.setPosition(0,0);
    this->background_rectangle.setSize({1150, 800});
    this->background_rectangle.setTexture(&background_texture);
    this->background_rectangle.setFillColor(sf::Color(255, 255, 255, 180));;

    std::pair<sf::Color, sf::Color> background_color = {sf::Color::Transparent, sf::Color::Transparent};
    std::pair<sf::Color, sf::Color> text_color = {sf::Color::White, sf::Color::Red};


    this->title = std::make_unique<ui::Text>("Minesweeper", font, 70, sf::Color(255,255,255, 255), sf::Vector2f(575, 300), ui::ORIGIN::C);
    this->start = std::make_unique<ui::Button>("> Start", this->font, 30, background_color, text_color, sf::Vector2f(575, 450), sf::Vector2f(190, 50), ui::ORIGIN::C);
    this->exit = std::make_unique<ui::Button>("> Exit", this->font, 30, background_color, text_color, sf::Vector2f(575, 550), sf::Vector2f(155, 50), ui::ORIGIN::C);
}

void Menu::update(){
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());

    if(this->start->update(position)){
        this->states->push(std::make_unique<BoardSelectState>(this->window, this->states, this->font));
    }
    else if(this->exit->update(position)){
        quit = true;
    }
}

void Menu::render(std::shared_ptr<sf::RenderTarget> target){
    target->draw(this->background_rectangle);
    target->draw(*this->title);
    target->draw(*this->start);
    target->draw(*this->exit);

}