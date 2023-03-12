#include "game.hpp"


Game::Game(int rows, int columns, int mines)
{
    this->rows = rows;
    this->columns = columns;
    this->mines = mines;
    this->board = Board(columns, rows, mines);
}

void Game::run()
{
    std::cout<<"Welcome to Mines!"<<std::endl;
    std::cout<<"Board dimensions: "<<rows<<"x"<<columns<<std::endl;
    std::cout<<"Mines: "<<mines<<std::endl;
    while(true)
    {
        
    }
}