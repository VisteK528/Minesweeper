#include <iostream>
#include "src/board.hpp"

int main()
{
    Board board(20, 20, 50);
    board.display_board();
    std::cout<<"This is a simple test"<<std::endl;
    return 0;
}