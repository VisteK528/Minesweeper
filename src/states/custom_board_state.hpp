//
// Created by piotr on 5/2/23.
//

#ifndef MINESWEEPER_CUSTOM_BOARD_STATE_HPP
#define MINESWEEPER_CUSTOM_BOARD_STATE_HPP

#include "state.hpp"
#include "../widgets.hpp"
#include "game_state.hpp"


class CustomBoardState: public State{
private:
    std::unique_ptr<ui::Text> title;
    std::unique_ptr<ui::Text> rows_text;
    std::unique_ptr<ui::Text> columns_text;
    std::unique_ptr<ui::Text> mines_text;

    std::unique_ptr<ui::Spinbox> rows_spinbox;
    std::unique_ptr<ui::Spinbox> columns_spinbox;
    std::unique_ptr<ui::Spinbox> mines_spinbox;

    std::unique_ptr<ui::Button> start_btn;
    std::unique_ptr<ui::Button> cancel_btn;

    //Variables
    std::pair<int, int> rows_range = {4, 40};
    std::pair<int, int> columns_range = {4, 40};
    std::pair<int, int> mines_percentage_range = {1, 40};

    int rows = 20;
    int columns = 20;
    int percentage_mines = 16;

    sf::Font font;
    sf::Image background;
    sf::Texture background_texture;
    sf::RectangleShape background_rectangle;

    void initVariables();
public:
    CustomBoardState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, sf::Font &font);

    void init() override {};
    void update() override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
};


#endif //MINESWEEPER_CUSTOM_BOARD_STATE_HPP
