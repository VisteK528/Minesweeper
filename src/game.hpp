#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include "widgets.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include <thread>
#include <iomanip>
#include <sstream>
#include "exceptions.hpp"
#include <math.h>

using namespace ui;

class Game
{
    private:
        // SFML variables
        std::unique_ptr<sf::RenderWindow> window;
        std::unique_ptr<sf::View> view;
        void initWindow();
        void initVariables();
        bool game_on = true;

        //Size
        unsigned int height = 800;
        unsigned int width = 1150;

        unsigned int board_height = 800;
        unsigned int board_width = 800;

        float width_ratio = 0;
        float height_ratio = 0;
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

        // Other
        unsigned int moves;

        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        std::chrono::time_point<std::chrono::high_resolution_clock> stop;
        std::chrono::minutes duration_m;
        std::chrono::seconds duration_s;


    public:
        Game(int rows, int columns, int mines);
        ~Game();
        void run();
        void runGraphics();
        void runGame();


};


#endif