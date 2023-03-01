#include "board.hpp"
#include <iostream>
#include <random>

Board::Board(int columns, int rows)
{
    // Generowanie losowych liczb
    std::random_device rd;
    const uint_least32_t seed = rd();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<uint_least32_t> distribute(1, 6);

    for(int i=0; i<rows; i++)
    {
        std::vector<Cell> row;
        for(int j=0; j<columns; j++)
        {
            row.push_back(Cell(i, j, distribute(generator)));
        }
        board_cells.push_back(row);
    }
}

Board::~Board(){};

void Board::display_board()
{
    for(auto row: Board::board_cells)
    {
        for(auto cell: row)
        {
            std::cout<<cell.get_value()<<' ';
        }
        std::cout<<std::endl;
    }
}