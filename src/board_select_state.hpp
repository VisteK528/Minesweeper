//
// Created by piotr on 4/30/23.
//

#ifndef MINESWEEPER_BOARD_SELECT_STATE_HPP
#define MINESWEEPER_BOARD_SELECT_STATE_HPP

#include "widgets.hpp"
#include "state.hpp"
#include "game_state.hpp"

class BoardSelectState: public State{
private:
    std::unique_ptr<ui::Text> title;
    std::unique_ptr<ui::Button> easy;
    std::unique_ptr<ui::Button> medium;
    std::unique_ptr<ui::Button> hard;
    std::unique_ptr<ui::Button> custom;
    std::unique_ptr<ui::Button> back;
    sf::Font font;

    sf::Image background;
    sf::Texture background_texture;
    sf::RectangleShape background_rectangle;

    void initVariables();
public:
    BoardSelectState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, sf::Font &font);

    void init(){};
    virtual void updateKeybinds();
    virtual void update();
    virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);
};

#endif //MINESWEEPER_BOARD_SELECT_STATE_HPP
