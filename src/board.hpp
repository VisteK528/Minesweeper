#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "cell.hpp"

class Board
{
    private:
        unsigned int uncover(int column, int row);
        bool check_if_winning();
        std::vector<std::vector<std::vector<Cell>>> board_cells;
        std::vector<std::vector<int>> selected_cells;
        int mines;
        int rows;
        int columns;
        int flagged_mines;

    public:
        std::vector<std::vector<std::vector<Cell>>> getBoard();
        void setBoard(std::vector<std::vector<std::vector<Cell>>> board);
        void load_board_with_random_values(unsigned int mines);
        int make_move(int column, int row, char move_type);
        void display_board(int mode);
        Board(){};
        Board(int rows, int columns, int mines);
        ~Board();
};

#endif