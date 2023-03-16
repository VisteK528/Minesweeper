#include "board.hpp"
#include <iostream>
#include <random>

Board::Board(int columns, int rows, int mines)
{
    this->columns = columns;
    this->rows = rows;
    this->mines = mines;
    this->flagged_mines = 0;

    load_board_with_random_values(mines);
}

Board::~Board(){};

std::vector<std::vector<std::vector<Cell>>> Board::getBoard()
{
    return this->board_cells;
}

void Board::setBoard(std::vector<std::vector<std::vector<Cell>>> board)
{
    this->board_cells = board;
}

void Board::load_board_with_random_values(unsigned int mines)
{
    // Generowanie losowych liczb
    std::random_device rd;
    const uint_least32_t seed = rd();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<uint_least32_t> rows_index(0, rows-1);
    std::uniform_int_distribution<uint_least32_t> columns_index(0, columns-1);

    board_cells.clear();

    // Init board
    for(int i=0; i<rows; i++)
    {
        std::vector<std::vector<Cell>> row;
        for(int j=0; j<columns; j++)
        {
            std::vector<Cell> cell_table;
            cell_table.push_back(Cell(i, j, 0));
            cell_table.push_back(Cell(i, j, 'X'));
            row.push_back(cell_table);
        }
        board_cells.push_back(row);
    }

    // Add mines
    while(mines > 0)
    {
        int row = rows_index(generator);
        int column = columns_index(generator);
        if(board_cells[row][column][0].getValue() != 9)
        {
            board_cells[row][column][0].setValue(9);
            mines--;
        }
    }

    // Count mines
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<columns; j++)
        {
            if(board_cells[i][j][0].getValue() != 9)
            {
                int mines = 0;
                for(int n=std::max(0,i-1); n<std::min(i+2, rows); n++)
                {
                    for(int k=std::max(0, j-1); k<std::min(j+2, columns); k++)
                    {
                        if(board_cells[n][k][0].getValue()==9)
                        {
                            mines++;
                        }
                    }
                }
                board_cells[i][j][0].setValue(mines);
            }
        }
    }
}

void Board::display_board(int mode)
{
    int i = 0;
    std::cout<<"    ";
    for(int j = 0; j < columns; j++)
    {
        std::cout<<j%10<<' ';
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    for(auto row: Board::board_cells)
    {
        if(i < 10)
        {
            std::cout<<i<<"   ";
        }
        else
        {
            std::cout<<i<<"  ";
        }
        for(auto cell: row)
        {
            if(mode==1)
            {
                std::cout<<cell[0].getValue()<<' ';
            }
            else
            {
                int value = cell[1].getValue();
                if(value == 88 or value == 70)
                {
                    std::cout<<(char)value<<' ';
                }
                else
                {
                    std::cout<<value<<' ';
                }
            }
        }
        std::cout<<std::endl;
        i++;
    }
}

unsigned int Board::uncover(int column, int row)
{
    int unflagged_mines = 0;
    int max_i = std::min(column+2, columns);
    int max_j = std::min(row+2, rows);
    for(int i = std::max(column-1, 0); i<max_i; i++)
    {
        for(int j = std::max(row-1,0); j<max_j; j++)
        {
            if(board_cells[j][i][1].getValue() == 'X')
            {
                int value = board_cells[j][i][0].getValue();
                char masked_value = board_cells[j][i][1].getValue();
                board_cells[j][i][1].setValue(value);
                if(value == 9 && masked_value != 'F')
                {
                    unflagged_mines++;
                }
                else if(value == 0)
                {
                    uncover(i, j);
                }
            }
        }
    }
    return unflagged_mines;
}

int Board::make_move(int column, int row, char move_type)
{
    /*
        Move types:
        1. Uncover
        2. Flag

        Returns:
        1. 0 - game carries on
        2. 1 - game over
        3. 5 - not valid coordinates
        4. 2 - game won
    */
    if(0<=column && column < columns && 0 <= row && row < rows)
    {
        int value = board_cells[row][column][0].getValue();
        char masked_value = board_cells[row][column][1].getValue();
        if(move_type=='1')
        {
            if(masked_value == 'X')
            {
                if(value != 9)
                {
                    if(value == 0)
                    {
                        uncover(column, row);
                    }
                    else
                    {
                        board_cells[row][column][1].setValue(value);
                    }
                }
                else
                {
                    return 1;   // Game over
                }
            }
            else
            {
                if(uncover(column, row) > 0)
                {
                    return 1;
                }
            }
        }
        else
        {
            if(masked_value == 'X')
            {
                board_cells[row][column][1].setValue('F');
                if(value == 9)
                {
                    flagged_mines ++;
                }
            }
            else if(masked_value == 'F')
            {
                board_cells[row][column][1].setValue('X');
                if(value == 9)
                {
                    flagged_mines --;
                }
            }
        }
        if(check_if_winning())
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 5;   // Not valid move
    }
}

bool Board::check_if_winning()
{
    int correctly_flagged = 0;
    for(auto row: Board::board_cells)
    {
        for(auto cell: row)
        {
            if(cell[1].getValue() == 'X')
            {
                return false;
            }
            if(cell[1].getValue() == 'F' && cell[0].getValue() == 9)
            {
                correctly_flagged++;
                if(correctly_flagged == flagged_mines && correctly_flagged == mines)
                {
                    return true;
                }
            }
        }
    }
    return false;
}