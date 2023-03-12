#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "cell.hpp"

class Board
{
    public:
        void load_board_with_random_values();
        void display_board();
        Board(int rows, int columns, int mines);
        ~Board();

    private:
        std::vector<std::vector<Cell>> board_cells;
};

#endif