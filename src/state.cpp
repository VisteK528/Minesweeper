//
// Created by piotr on 4/29/23.
//

#include "state.hpp"

State::State(std::shared_ptr<sf::RenderWindow> window){
    this->window = window;
    this->quit = false;
}

State::~State(){

}

void State::checkForQuit(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        this->quit = true;
    }
}

const bool& State::getQuit() const{
    return this->quit;
}