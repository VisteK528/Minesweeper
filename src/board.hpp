#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "cell.hpp"

typedef enum {CARRY_ON=0, GAME_OVER=1, INVALID_INPUT=3, WIN=4} RESULTS;
typedef enum {COVERED=88, FLAGGED=70, QUESTION=63, EXPLODED=111, OTHER_EXPLODED=87, INVALIDLY_FLAGGED=73} MASKED_VALUES;
typedef enum {EMPTY=0, MINE=9} COVERED_VALUES;
typedef enum {UNCOVER=1, FLAG=2} MOVES;

//         1. 0 - game carries on
//         2. 1 - game over
//         3. 5 - not valid coordinates
//         4. 2 - game won

class Board
{
    private:
        std::vector<std::vector<Cell>> board_cells;
        unsigned int mines;
        unsigned int correctly_flagged;
        unsigned int flagged_mines;

        int rows;
        int columns;

        //Methods
        unsigned int uncover(int column, int row);
        bool checkIfInsideRect(Cell cell, int row, int column) const;
        bool checkIfUncoverable(int row, int column) const;
        bool checkIfWinning() const;
        void gameOverUncover(int row, int column);

    public:
        Board(){};
        Board(int rows, int columns, int mines);

        std::vector<std::vector<Cell>> getBoard() const;
        void setBoard(std::vector<std::vector<Cell>> board);
        void loadBoardWithRandomValues(unsigned int mines);
        void displayBoard(int mode);
        unsigned int getFlaggedMines() const {return flagged_mines;}
        RESULTS makeMove(int column, int row, MOVES move_type);
};

#endif