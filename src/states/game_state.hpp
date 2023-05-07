//
// Created by piotr on 4/29/23.
//

#ifndef MINESWEEPER_GAME_STATE_HPP
#define MINESWEEPER_GAME_STATE_HPP

#include "../board.hpp"
#include "state.hpp"
#include <chrono>
#include "../exceptions.hpp"
#include "../gui_manager.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <SFML/Graphics.hpp>

class GameState: public State{
private:
    RESULTS result = CARRY_ON;
    bool game_on = true;

    //Size
    unsigned int height = 800;
    unsigned int width = 1150;

    unsigned int board_height = 800;
    unsigned int board_width = 800;

    std::pair<double, double> board_ratio = {0, 0};
    sf::Vector2i offset = {0, 0};

    float position_size = 0;
    std::pair<unsigned int, unsigned int> tile_texture_size = {512, 512};

    // General variables
    int mines;
    int rows;
    int columns;
    unsigned int moves;

    // Graphics
    sf::Image image;
    sf::Texture my_texture;
    sf::Sprite my_sprite;
    std::vector<std::shared_ptr<sf::Texture>> textures;
    std::vector<std::vector<std::shared_ptr<sf::Sprite>>> board_sprites;

    // Board
    Board board;

    // Time variables
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> stop;
    std::chrono::minutes duration_m;
    std::chrono::seconds duration_s;

    // Gui widgets
    std::shared_ptr<GuiManager> gui_manager;
    std::unique_ptr<ui::Text> time_info;
    std::unique_ptr<ui::Text> mines_info;
    std::unique_ptr<ui::Button> play_again_btn;
    std::unique_ptr<ui::Button> change_difficulty_btn;

    // Game methods
    void updateStateDimensions() override;

    void initVariables();
    void updateBoard();
    void renderSprites();
    void loadTextures();
    void restart();
public:
    GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager, int rows, int columns, int mines);
    virtual ~GameState(){};

    void init() override;
    void update() override;
    void handleEvent(const sf::Event& e) override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
};


#endif //MINESWEEPER_GAME_STATE_HPP