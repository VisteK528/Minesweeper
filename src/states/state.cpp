#include "state.hpp"

State::State(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states){
    this->window = window;
    this->states = states;
    this->quit = false;
}

State::~State(){}

const bool& State::getQuit() const{
    return this->quit;
}

void State::updateStateDimensions() {
    sf::Vector2f size = this->window->getView().getSize();
    change_ratio = {size.x/1150., size.y/800.};
}
