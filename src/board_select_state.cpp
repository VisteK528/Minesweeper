//
// Created by piotr on 4/30/23.
//

#include "board_select_state.hpp"

BoardSelectState::BoardSelectState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>>states, sf::Font& font): State(window, states) {
    this->title = nullptr;
    this->easy = nullptr;
    this->medium = nullptr;
    this->hard = nullptr;
    this->custom = nullptr;
    this->back = nullptr;
    this->font = font;
    initVariables();
}

void BoardSelectState::initVariables() {
    this->background.loadFromFile("textures/menu_background.png");
    this->background_texture.loadFromImage(background);

    this->background_rectangle.setPosition(0,0);
    this->background_rectangle.setSize({1150, 800});
    this->background_rectangle.setTexture(&background_texture);
    this->background_rectangle.setFillColor(sf::Color(255, 255, 255, 180));;

    std::pair<sf::Color, sf::Color> background_color = {sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200)};
    std::pair<sf::Color, sf::Color> text_color = {sf::Color::White, sf::Color::Red};


    this->title = std::make_unique<ui::Text>("Minesweeper", font, 40, sf::Color(255,255,255, 255), sf::Vector2f(50, 50), ui::ORIGIN::NW);
    this->easy = std::make_unique<ui::Button>("> Easy", this->font, 30, background_color, text_color, sf::Vector2f(425, 400), sf::Vector2f(220, 70), ui::ORIGIN::C);
    this->medium = std::make_unique<ui::Button>("> Medium", this->font, 30, background_color, text_color, sf::Vector2f(725, 400), sf::Vector2f(250, 70), ui::ORIGIN::C);
    this->hard = std::make_unique<ui::Button>("> Hard", this->font, 30, background_color, text_color, sf::Vector2f(425, 600), sf::Vector2f(220, 70), ui::ORIGIN::C);
    this->custom = std::make_unique<ui::Button>("> Custom", this->font, 30, background_color, text_color, sf::Vector2f(725, 600), sf::Vector2f(250, 70), ui::ORIGIN::C);
    this->back = std::make_unique<ui::Button>("> Back", this->font, 20, background_color, text_color, sf::Vector2f(1125, 775), sf::Vector2f(200, 50), ui::ORIGIN::SE);
}

void BoardSelectState::updateKeybinds(){
    this->checkForQuit();
}

void BoardSelectState::update(){
    updateKeybinds();
    sf::Vector2i position = sf::Mouse::getPosition(*this->window);

    if(this->back->update(static_cast<sf::Vector2f>(position))){
        quit= true;
    }
    if(this->easy->update(static_cast<sf::Vector2f>(position))){
        states->push(std::make_unique<GameState>(this->window, this->states, 8, 8, 10));
        states->top()->init();
    }
    if(this->medium->update(static_cast<sf::Vector2f>(position))){
        states->push(std::make_unique<GameState>(this->window, this->states, 16, 16, 40));
        states->top()->init();
    }
    if(this->hard->update(static_cast<sf::Vector2f>(position))){
        states->push(std::make_unique<GameState>(this->window, this->states, 16, 30, 99));
        states->top()->init();
    }
    if(this->custom->update(static_cast<sf::Vector2f>(position))){
        states->push(std::make_unique<GameState>(this->window, this->states, 16, 16, 40));
        states->top()->init();
    }

}

void BoardSelectState::render(std::shared_ptr<sf::RenderTarget> target){
    target->draw(this->background_rectangle);
    target->draw(*this->title);
    target->draw(*this->easy);
    target->draw(*this->medium);
    target->draw(*this->hard);
    target->draw(*this->custom);
    target->draw(*this->back);

}