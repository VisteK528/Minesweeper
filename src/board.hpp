#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "cell.hpp"

typedef enum {CARRY_ON=0, GAME_OVER=1, INVALID_INPUT=3, WIN=4} RESULTS;

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
        bool check_if_uncoverable(int row, int column) const;
        bool check_if_winning() const;
        void gameOverUncover(int row, int column);

    public:
        Board(){};
        Board(int rows, int columns, int mines);

        std::vector<std::vector<Cell>> getBoard() const;
        void setBoard(std::vector<std::vector<Cell>> board);
        void load_board_with_random_values(unsigned int mines);
        void display_board(int mode);
        unsigned int getFlaggedMines() const {return flagged_mines;}
        RESULTS make_move(int column, int row, char move_type);
};

#endif