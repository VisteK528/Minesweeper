#include "board.hpp"
#include <iostream>
#include <random>

Board::Board(int columns, int rows, int mines)
{
    // Generowanie losowych liczb
    std::random_device rd;
    const uint_least32_t seed = rd();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<uint_least32_t> rows_index(0, rows-1);
    std::uniform_int_distribution<uint_least32_t> columns_index(0, columns-1);

    // Init board
    for(int i=0; i<rows; i++)
    {
        std::vector<Cell> row;
        for(int j=0; j<columns; j++)
        {
            row.push_back(Cell(i, j, 0));
        }
        board_cells.push_back(row);
    }

    // Add mines
    while(mines > 0)
    {
        int row = rows_index(generator);
        int column = columns_index(generator);
        if(board_cells[row][column].get_value() != 9)
        {
            board_cells[row][column].set_value(9);
            mines--;
        }
    }

    // Count mines
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<columns; j++)
        {
            if(board_cells[i][j].get_value() != 9)
            {
                int mines = 0;
                for(int n=std::max(0,i-1); n<std::min(i+2, rows); n++)
                {
                    for(int k=std::max(0, j-1); k<std::min(j+2, columns); k++)
                    {
                        if(board_cells[n][k].get_value()==9)
                        {
                            mines++;
                        }
                    }
                }
                board_cells[i][j].set_value(mines);
            }
        }
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