#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "cell.hpp"

class Board
{
    private:
        std::vector<std::vector<Cell>> board_cells;
        std::vector<std::vector<int>> selected_cells;
        unsigned int mines;
        unsigned int flagged_mines;

        int rows;
        int columns;

        //Methods
        unsigned int uncover(int column, int row);
        bool check_if_winning() const;
        void gameOverUncover(unsigned int row, unsigned int column);

    public:
    Board(){};
        Board(int rows, int columns, int mines);

        std::vector<std::vector<Cell>> getBoard() const;
        void setBoard(std::vector<std::vector<Cell>> board);
        void load_board_with_random_values(unsigned int mines);
        int make_move(int column, int row, char move_type);
        void display_board(int mode);
};

#endif