//
// Created by piotr on 4/29/23.
//

#include "state_manager.hpp"

StateManager::StateManager() {
    this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1150, 800), "Minesweeper");
    this->font.loadFromFile("textures/mine-sweeper.ttf");
    pushState(std::make_unique<Menu>(this->window, this->font));
}

StateManager::~StateManager() {
    while(!this->states.empty()){
        states.pop();
    }
}
void StateManager::pushState(std::unique_ptr<State> state) {
    this->states.push(std::move(state));
}

void StateManager::popState() {
    if(!states.empty()){
        states.top();
        states.pop();
    }
}

void StateManager::render() {
    this->window->clear();
    if(!this->states.empty()){
        this->states.top()->render(this->window);
    }
    this->window->display();
}

void StateManager::update() {
    updateSFMLEvents();
    if(!this->states.empty()){
        this->states.top()->update();
    }
}

void StateManager::updateSFMLEvents() {
    while(this->window->pollEvent(e)){
        if(this->e.type == sf::Event::Closed){
            this->window->close();
        }
    }
}

void StateManager::run() {
    while(this->window->isOpen()){
        update();
        render();
    }
}