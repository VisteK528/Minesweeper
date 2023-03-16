#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include <iostream>

class Game
{
    private:
        bool game_on = true;
        int rows;
        int columns;
        int mines;
        Board board;

    public:
        Game(int rows, int columns, int mines);
        void run();


};


#endif