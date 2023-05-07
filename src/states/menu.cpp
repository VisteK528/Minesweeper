#include "menu.hpp"

Menu::Menu(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager): State(window, states) {
    this->title = nullptr;
    this->start = nullptr;
    this->exit = nullptr;
    this->gui_manager = std::move(gui_manager);
    initVariables();
}

void Menu::initVariables() {
    this->background.loadFromFile("textures/menu_background.png");
    this->background_texture.loadFromImage(background);

    this->background_rectangle.setPosition(0,0);
    this->background_rectangle.setSize({1150, 800});
    this->background_rectangle.setTexture(&background_texture);
    this->background_rectangle.setFillColor(sf::Color(255, 255, 255, 180));;

    this->title = gui_manager->createText("Minesweeper", 70, sf::Vector2f(575, 300), ui::ORIGIN::C);
    this->start = gui_manager->createButton("> Start", 30, sf::Vector2f(575, 450), sf::Vector2f(250, 70), ui::ORIGIN::C);
    this->exit = gui_manager->createButton("> Exit",30, sf::Vector2f(575, 550), sf::Vector2f(220, 60), ui::ORIGIN::C);
}

void Menu::update(){
    updateStateDimensions();
    this->start->updatePosition(change_ratio, this->window);
    this->exit->updatePosition(change_ratio, this->window);
    this->title->updatePosition(change_ratio, this->window);

    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());
    this->start->update(position);
    this->exit->update(position);

    this->background_rectangle.setScale((float)change_ratio.first, (float)change_ratio.second);
    this->background_rectangle.setPosition((1150.-this->window->getSize().x)/2., (800.-this->window->getSize().y)/2.);
}

void Menu::handleEvent(const sf::Event &e) {
    updateStateDimensions();
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());

    if(this->start->handleInput(position, e)){
        this->states->push(std::make_unique<BoardSelectState>(this->window, this->states, this->gui_manager));
    }
    else if(this->exit->handleInput(position, e)){
        quit = true;
    }
}

void Menu::render(std::shared_ptr<sf::RenderTarget> target){
    target->draw(this->background_rectangle);
    target->draw(*this->title);
    target->draw(*this->start);
    target->draw(*this->exit);

}