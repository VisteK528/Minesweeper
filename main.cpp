#include <iostream>
#include "src/board.hpp"

int main()
{
     Board board(20, 20, 50);
    //Board board(4, 4, 2);
    int result;
    while(true)
    {
        std::system("clear");
        board.display_board(0);
        int row = 0;
        int column = 0;
        char move;
        std::cout<<"Row: ";
        std::cin>>row;
        std::cout<<"Column: ";
        std::cin>>column;
        std::cout<<"Move: ";
        std::cin>>move;
        std::cout<<std::endl;
        std::cout<<std::endl;
        result = board.make_move(column, row, move);
        std::system("clear");
        board.display_board(0);
        std::cout<<std::endl;
        if(result == 1)
        {
            std::cout<<"Game over!"<<std::endl;
            std::cout<<"Press enter to continue...";
            std::getchar();
            std::getchar();
            break;
        }
        else if(result == 5)
        {
            std::cout<<"Invalid input!"<<std::endl;
            std::cout<<"Press enter to continue...";
            std::getchar();
            std::getchar();
            continue;
        }
        else if(result == 2)
        {
            std::cout<<"YOU WON!!!"<<std::endl;
            std::cout<<"Press enter to continue...";
            std::getchar();
            std::getchar();
            break;
        }
    }
    return 0;
}