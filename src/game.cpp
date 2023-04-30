//
// Created by piotr on 4/29/23.
//

#include "game.hpp"

Game::Game() {
    this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1150, 800), "Minesweeper");
    this->view = std::make_unique<sf::View>(window->getDefaultView());
    this->states = std::make_shared<std::stack<std::unique_ptr<State>>>();
    this->font.loadFromFile("textures/mine-sweeper.ttf");
    pushState(std::make_unique<Menu>(this->window, this->states, this->font));
    this->states->top()->init();
}

Game::~Game() {
    while(!this->states->empty()){
        states->pop();
    }
}
void Game::pushState(std::unique_ptr<State> state) {
    this->states->push(std::move(state));
}

void Game::popState() {
    if(!states->empty()){
        states->top();
        states->pop();
    }
}

void Game::render() {
    this->window->clear();
    if(!this->states->empty()){
        this->states->top()->render(this->window);
    }
    this->window->display();
}

void Game::update() {
    updateSFMLEvents();
    if(!this->states->empty()){
        this->states->top()->update();
        if(this->states->top()->getQuit()){
            this->states->pop();
            if(!this->states->empty()){
                this->states->top()->init();
            }
        }
    }
}

void Game::updateSFMLEvents() {
    while(this->window->pollEvent(e)){
        if(this->e.type == sf::Event::Closed){
            this->window->close();
        }
        else if(this->e.type == sf::Event::Resized) {
            sf::Vector2f view_size = {static_cast<float>(this->e.size.width), static_cast<float>(this->e.size.height)};
            view->setSize(view_size);
            window->setView(*view);
        }
    }
}

void Game::run() {
    while(this->window->isOpen()){
        update();
        render();
    }
}