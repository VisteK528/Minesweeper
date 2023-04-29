//
// Created by piotr on 4/29/23.
//

#ifndef MINESWEEPER_GAME_STATE_HPP
#define MINESWEEPER_GAME_STATE_HPP


#include "state.hpp"

class GameState: public State{
public:
    GameState(std::shared_ptr<sf::RenderWindow> window): State(window){};
    virtual ~GameState(){};

    void updateKeybinds() override;
    void update() override;
    void render(std::shared_ptr<sf::RenderTarget> target = nullptr) override;
};


#endif //MINESWEEPER_GAME_STATE_HPP
