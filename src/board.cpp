#include "board.hpp"
#include <iostream>
#include <random>

Board::Board(int columns, int rows, int mines)
{
    this->columns = columns;
    this->rows = rows;
    this->mines = mines;
    this->flagged_mines = 0;
    this->correctly_flagged = 0;

    load_board_with_random_values(mines);
}

std::vector<std::vector<Cell>> Board::getBoard() const
{
    return this->board_cells;
}

void Board::setBoard(std::vector<std::vector<Cell>> board)
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
        std::vector<Cell> row;
        for(int j=0; j<columns; j++)
        {
            row.push_back(Cell(j, i, 0));
        }
        board_cells.push_back(row);
    }

    // Add mines
    while(mines > 0)
    {
        int row = rows_index(generator);
        int column = columns_index(generator);
        if(board_cells[row][column].getValue() != 9)
        {
            board_cells[row][column].setValue(9);
            mines--;
        }
    }

    // Count mines
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<columns; j++)
        {
            if(board_cells[i][j].getValue() != 9)
            {
                int mines = 0;
                for(int n=std::max(0,i-1); n<std::min(i+2, rows); n++)
                {
                    for(int k=std::max(0, j-1); k<std::min(j+2, columns); k++)
                    {
                        if(board_cells[n][k].getValue()==9)
                        {
                            mines++;
                        }
                    }
                }
                board_cells[i][j].setValue(mines);
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
                std::cout<<cell.getValue()<<' ';
            }
            else
            {
                int value = cell.getMaskedValue();
                if(value == 88 || value == 70 || value == 111 || value == 87 || value == 73 || value == 63)
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

unsigned int Board::uncover(int row, int column)
{
    int unflagged_mines = 0;
    int max_i = std::min(row+2, rows);
    int max_j = std::min(column+2, columns);

    for(int i = std::max(row-1, 0); i<max_i; i++)
    {
        for(int j = std::max(column-1,0); j<max_j; j++)
        {
            if(board_cells[i][j].getMaskedValue() == 'X' || board_cells[i][j].getMaskedValue() == '?')
            {
                int value = board_cells[i][j].getValue();
                char masked_value = board_cells[i][j].getMaskedValue();
                board_cells[i][j].setMaskedValue(value);
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

void Board::gameOverUncover(int row, int column)
{
    for(auto& row_vect: board_cells)
    {
        for(auto& cell: row_vect)
        {
            if((cell.getY() >= row-1 && cell.getY() <row+2 && cell.getX() >= column-1 && cell.getX() < column+2 && cell.getMaskedValue() == 9 && cell.getValue() == 9) || (cell.getY() == row && cell.getX() == column && (cell.getMaskedValue() == 88 || cell.getMaskedValue() == 63) && cell.getValue() == 9))
            {
                cell.setMaskedValue(111);   // Set game over mine field to 'o'
            }
            else if(cell.getValue() == 9 && cell.getMaskedValue() == 88)
            {
                cell.setMaskedValue(87);            // Set all remaining bombs fields to "W", (Went off)
            }
            else if(cell.getMaskedValue() == 70 && cell.getValue() != 9)
            {
                cell.setMaskedValue(73);            // Set all invalidly flagged bombs to "I", (Invalid)
            }
        }
    }
}

bool Board::check_if_uncoverable(int row, int column) const
{
    int flagged = 0;
    for(int i=std::max(0, row-1); i<std::min(rows, row+2); i++)
    {
        for(int j=std::max(0, column-1); j<std::min(columns, column+2); j++)
        {
            if(board_cells[i][j].getMaskedValue() == 'F')
            {
                flagged++;
            }
        }
    }
    if(flagged == board_cells[row][column].getMaskedValue())
    {
        return true;
    }
    return false;
}

RESULTS Board::make_move(int column, int row, char move_type)
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
        int value = board_cells[row][column].getValue();
        char masked_value = board_cells[row][column].getMaskedValue();
        if(move_type=='1')
        {
            if(masked_value == 'X' || masked_value == '?')
            {
                if(value != 9)
                {
                    if(value == 0)
                    {
                        uncover(row, column);
                    }
                    else
                    {
                        board_cells[row][column].setMaskedValue(value);
                    }
                }
                else
                {
                    gameOverUncover(row, column);
                    return GAME_OVER;   // Game over
                }
            }
            else
            {
                if(check_if_uncoverable(row, column))
                {
                    if(uncover(row, column) > 0)
                    {
                        gameOverUncover(row, column);
                        return GAME_OVER;
                    }
                }
            }
        }
        else
        {
            if(masked_value == 'X')
            {
                board_cells[row][column].setMaskedValue('F');
                if(flagged_mines < mines)
                {
                    flagged_mines ++;
                    if(value == 9)
                    {
                        correctly_flagged ++;
                    }
                }
            }
            else if(masked_value == 'F'){
                board_cells[row][column].setMaskedValue('?');
                if(flagged_mines > 0)
                {
                    flagged_mines --;
                    if(value == 9)
                    {
                        correctly_flagged --;
                    }
                }
            }
            else if(masked_value == '?'){
                board_cells[row][column].setMaskedValue('X');
            }
        }
        if(check_if_winning())
        {
            return WIN;
        }
        else
        {
            return CARRY_ON;
        }
    }
    else
    {
        return INVALID_INPUT;   // Not valid move
    }
}

bool Board::check_if_winning() const
{
    for(auto row: Board::board_cells)
    {
        for(auto cell: row)
        {
            if(cell.getMaskedValue() == 'X')
            {
                return false;
            }
        }
    }
    if(correctly_flagged == flagged_mines && correctly_flagged == mines)
    {
        return true;
    }
    return false;
}