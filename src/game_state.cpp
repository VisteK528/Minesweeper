//
// Created by piotr on 4/29/23.
//

#include "game_state.hpp"

void GameState::update() {
    this->updateKeybinds();
}

void GameState::render(std::shared_ptr<sf::RenderTarget> target) {

}

void GameState::updateKeybinds() {
    this->checkForQuit();
}
