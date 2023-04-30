#include "board.hpp"
#include <iostream>
#include <random>

Board::Board(int columns, int rows, int mines){
    this->columns = columns;
    this->rows = rows;
    this->mines = mines;
    this->flagged_mines = 0;
    this->correctly_flagged = 0;

    loadBoardWithRandomValues(mines);
}

std::vector<std::vector<Cell>> Board::getBoard() const{
    return this->board_cells;
}

void Board::setBoard(std::vector<std::vector<Cell>> board){
    this->board_cells = board;
}

void Board::loadBoardWithRandomValues(unsigned int mines) {
    this->flagged_mines = 0;
    this->correctly_flagged = 0;

    // Generating random numbers
    std::random_device rd;
    const uint_least32_t seed = rd();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<uint_least32_t> rows_index(0, rows-1);
    std::uniform_int_distribution<uint_least32_t> columns_index(0, columns-1);

    board_cells.clear();

    // Init board
    for(int i=0; i<rows; i++){
        std::vector<Cell> row;
        for(int j=0; j<columns; j++){
            row.push_back(Cell(j, i, EMPTY));
        }
        board_cells.push_back(row);
    }

    // Add mines
    while(mines > 0){
        int row = rows_index(generator);
        int column = columns_index(generator);
        if(board_cells[row][column].getValue() != MINE){
            board_cells[row][column].setValue(MINE);
            mines--;
        }
    }

    // Count mines
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(board_cells[i][j].getValue() != MINE){
                int mines = 0;
                for(int n=std::max(0,i-1); n<std::min(i+2, rows); n++){
                    for(int k=std::max(0, j-1); k<std::min(j+2, columns); k++){
                        if(board_cells[n][k].getValue()==MINE){
                            mines++;
                        }
                    }
                }
                board_cells[i][j].setValue(mines);
            }
        }
    }
}

void Board::displayBoard(int mode) {
    int i = 0;
    std::cout<<"    ";
    for(int j = 0; j < columns; j++){
        std::cout<<j%10<<' ';
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    for(const auto& row: Board::board_cells){
        if(i < 10){
            std::cout<<i<<"   ";
        }
        else{
            std::cout<<i<<"  ";
        }
        for(const auto& cell: row){
            if(mode==1){
                std::cout<<cell.getValue()<<' ';
            }
            else{
                int value = cell.getMaskedValue();
                if(value == COVERED || value == FLAGGED || value == EXPLODED || value == OTHER_EXPLODED || value == INVALIDLY_FLAGGED || value == QUESTION){
                    std::cout<<(char)value<<' ';
                }
                else{
                    std::cout<<value<<' ';
                }
            }
        }
        std::cout<<std::endl;
        i++;
    }
}

unsigned int Board::uncover(int row, int column){
    int unflagged_mines = 0;
    int max_i = std::min(row+2, rows);
    int max_j = std::min(column+2, columns);

    for(int i = std::max(row-1, 0); i<max_i; i++){
        for(int j = std::max(column-1,0); j<max_j; j++){
            if(board_cells[i][j].getMaskedValue() == COVERED || board_cells[i][j].getMaskedValue() == QUESTION){
                int value = board_cells[i][j].getValue();
                char masked_value = board_cells[i][j].getMaskedValue();
                board_cells[i][j].setMaskedValue(value);
                if(value == MINE && masked_value != FLAGGED){
                    unflagged_mines++;
                }
                else if(value == EMPTY){
                    uncover(i, j);
                }
            }
        }
    }
    return unflagged_mines;
}

void Board::gameOverUncover(int row, int column){
    for(auto& row_vect: board_cells){
        for(auto& cell: row_vect){
            if((checkIfInsideRect(cell, row, column) && cell.getMaskedValue() == MINE && cell.getValue() == MINE) || (cell.getY() == row && cell.getX() == column && (cell.getMaskedValue() == COVERED || cell.getMaskedValue() == QUESTION) && cell.getValue() == MINE)){
                cell.setMaskedValue(EXPLODED);           // Set game over mine field to 'o'
            }
            else if(cell.getValue() == MINE && cell.getMaskedValue() == COVERED){
                cell.setMaskedValue(OTHER_EXPLODED);            // Set all remaining bombs fields to "W", (Went off)
            }
            else if(cell.getMaskedValue() == FLAGGED && cell.getValue() != MINE){
                cell.setMaskedValue(INVALIDLY_FLAGGED);            // Set all invalidly flagged bombs to "I", (Invalid)
            }
        }
    }
}

bool Board::checkIfUncoverable(int row, int column) const{
    int flagged = 0;
    for(int i=std::max(0, row-1); i<std::min(rows, row+2); i++){
        for(int j=std::max(0, column-1); j<std::min(columns, column+2); j++){
            if(board_cells[i][j].getMaskedValue() == FLAGGED){
                flagged++;
            }
        }
    }
    if(flagged == board_cells[row][column].getMaskedValue()) return true;
    return false;
}

bool Board::checkIfInsideRect(Cell cell, int row, int column) const{
    int y = cell.getY();
    int x = cell.getX();
    if(y >= row-1 && y < row + 2 && x >= column -1 && x < column+2) return true;
    return false;
}

RESULTS Board::makeMove(int column, int row, MOVES move_type){
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
    if(0<=column && column < columns && 0 <= row && row < rows){
        int value = board_cells[row][column].getValue();
        char masked_value = board_cells[row][column].getMaskedValue();
        if(move_type==UNCOVER){
            if(masked_value == COVERED || masked_value == QUESTION){
                if(value != MINE){
                    if(value == EMPTY){
                        uncover(row, column);
                    }
                    else{
                        board_cells[row][column].setMaskedValue(value);
                    }
                }
                else{
                    gameOverUncover(row, column);
                    return GAME_OVER;   // Game over
                }
            }
            else{
                if(checkIfUncoverable(row, column)){
                    if(uncover(row, column) > 0){
                        gameOverUncover(row, column);
                        return GAME_OVER;
                    }
                }
            }
        }
        else
        {
            if(masked_value == COVERED){
                if(flagged_mines < mines){
                    board_cells[row][column].setMaskedValue(FLAGGED);
                    flagged_mines ++;
                    if(value == MINE){
                        correctly_flagged ++;
                    }
                }
                else{
                    board_cells[row][column].setMaskedValue(QUESTION);
                }
            }
            else if(masked_value == FLAGGED){
                board_cells[row][column].setMaskedValue(QUESTION);
                if(flagged_mines > 0){
                    flagged_mines --;
                    if(value == MINE){
                        correctly_flagged --;
                    }
                }
            }
            else if(masked_value == QUESTION){
                board_cells[row][column].setMaskedValue(COVERED);
            }
        }
        if(checkIfWinning()){
            return WIN;
        }
        else{
            return CARRY_ON;
        }
    }
    else{
        return INVALID_INPUT;   // Not valid move
    }
}

bool Board::checkIfWinning() const
{
    for(const auto& row: Board::board_cells){
        for(auto cell: row){
            if(cell.getMaskedValue() == COVERED) return false;
        }
    }
    if(correctly_flagged == flagged_mines && correctly_flagged == mines) return true;
    return false;
}