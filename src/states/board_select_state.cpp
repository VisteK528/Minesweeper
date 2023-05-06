#include "board_select_state.hpp"

BoardSelectState::BoardSelectState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>>states, std::shared_ptr<GuiManager> gui_manager): State(window, states) {
    this->title = nullptr;
    this->easy = nullptr;
    this->medium = nullptr;
    this->hard = nullptr;
    this->custom = nullptr;
    this->back = nullptr;
    this->gui_manager = std::move(gui_manager);
    initVariables();
}

void BoardSelectState::initVariables() {
    this->background.loadFromFile("textures/menu_background.png");
    this->background_texture.loadFromImage(background);

    this->background_rectangle.setPosition(0,0);
    this->background_rectangle.setSize({1150, 800});
    this->background_rectangle.setTexture(&background_texture);
    this->background_rectangle.setFillColor(sf::Color(255, 255, 255, 180));

    this->title = gui_manager->createText("Minesweeper", 40, sf::Vector2f(50, 50), ui::ORIGIN::NW);
    this->easy = gui_manager->createButton("> Easy", 30, sf::Vector2f(425, 400), sf::Vector2f(220, 70), ui::ORIGIN::C);
    this->medium = gui_manager->createButton("> Medium", 30, sf::Vector2f(725, 400), sf::Vector2f(250, 70), ui::ORIGIN::C);
    this->hard = gui_manager->createButton("> Hard", 30, sf::Vector2f(425, 600), sf::Vector2f(220, 70), ui::ORIGIN::C);
    this->custom = gui_manager->createButton("> Custom", 30, sf::Vector2f(725, 600), sf::Vector2f(250, 70), ui::ORIGIN::C);
    this->back = gui_manager->createButton("> Back", 20, sf::Vector2f(1125, 775), sf::Vector2f(200, 50), ui::ORIGIN::SE);
}

void BoardSelectState::update(){
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());

    if(this->back->update(static_cast<sf::Vector2f>(position))){
        quit= true;
    }
    if(this->easy->update(static_cast<sf::Vector2f>(position))){
        states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager, 8, 8, 10));
        states->top()->init();
    }
    if(this->medium->update(static_cast<sf::Vector2f>(position))){
        states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager,16, 16, 40));
        states->top()->init();
    }
    if(this->hard->update(static_cast<sf::Vector2f>(position))){
        states->push(std::make_unique<GameState>(this->window, this->states, this->gui_manager,16, 30, 99));
        states->top()->init();
    }
    if(this->custom->update(static_cast<sf::Vector2f>(position))){
        states->push(std::make_unique<CustomBoardState>(this->window, this->states, this->gui_manager));
        states->top()->init();
    }

}

void BoardSelectState::handleEvent(const sf::Event &e) {

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