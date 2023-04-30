//
// Created by piotr on 4/29/23.
//

#ifndef MINESWEEPER_GAME_STATE_HPP
#define MINESWEEPER_GAME_STATE_HPP

#include "board.hpp"
#include "state.hpp"
#include <chrono>
#include "exceptions.hpp"
#include "widgets.hpp"
#include <iostream>
#include <iomanip>

class GameState: public State{
private:
    RESULTS result = CARRY_ON;
    bool button_left_pressed = false;
    bool button_right_pressed = false;

    bool game_on = true;
    void initVariables();

    //Size
    unsigned int height = 800;
    unsigned int width = 1150;

    unsigned int board_height = 800;
    unsigned int board_width = 800;

    std::pair<double, double> board_ratio = {0, 0};

    float tile_size = 0;
    float position_size = 0;
    std::pair<unsigned int, unsigned int> tile_texture_size = {512, 512};

    // General variables
    int mines;
    int rows;
    int columns;

    sf::Image image;
    sf::Texture my_texture;
    sf::Font font;
    sf::Sprite my_sprite;

    std::vector<std::shared_ptr<sf::Texture>> textures;
    std::vector<std::vector<std::shared_ptr<sf::Sprite>>> board_sprites;

    // Board
    Board board;
    void updateBoard();
    void renderSprites();
    void loadTextures();
    void restart();

    // Other
    unsigned int moves;

    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> stop;
    std::chrono::minutes duration_m;
    std::chrono::seconds duration_s;

    std::unique_ptr<ui::Text> time_info;
    std::unique_ptr<ui::Text> mines_info;

    std::unique_ptr<ui::Button> play_again;
    std::unique_ptr<ui::Button> change_difficulty;
public:
    GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, int rows, int columns, int mines);
    virtual ~GameState(){};

    void init() override;
    void updateKeybinds() override;
    void update() override;
    void render(std::shared_ptr<sf::RenderTarget> target = nullptr) override;
};


#endif //MINESWEEPER_GAME_STATE_HPP