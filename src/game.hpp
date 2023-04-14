#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include <thread>

class Game
{
    private:
        // SFML variables
        std::unique_ptr<sf::RenderWindow> window;
        sf::Event ev;
        void initWindow();
        void initVariables();
        bool game_on = true;

        // General variables
        int mines;
        int rows;
        int columns;

        sf::Texture my_texture;
        sf::Sprite my_sprite;

        std::vector<std::shared_ptr<sf::Texture>> textures;
        std::vector<std::vector<std::shared_ptr<sf::Sprite>>> board_sprites;

        // Board
        Board board;
        void updateBoard();
        void renderSprites();
        void loadTextures();

    public:
        Game(int rows, int columns, int mines);
        void run();
        void runGraphics();
        void runGame();


};


#endif