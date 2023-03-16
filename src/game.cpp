#include "game.hpp"


Game::Game(int rows, int columns, int mines)
{
    this->rows = rows;
    this->columns = columns;
    this->mines = mines;
    this->board = Board(columns, rows, mines);
}

void Game::run()
{
    std::cout<<"Welcome to Mines!"<<std::endl;
    std::cout<<"Board dimensions: "<<rows<<"x"<<columns<<std::endl;
    std::cout<<"Mines: "<<mines<<std::endl;
    int result;
    while(game_on)
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
        char choice;
        switch(result)
        {
            case 1:
                std::cout<<"Game over!"<<std::endl;
                std::cout<<"Do you want to play again? y/n: ";
                std::cin>>choice;
                if(choice == 'n')
                {
                    game_on = false;
                }
                else
                {
                    board.load_board_with_random_values(mines);
                }
                break;
            case 5:
                std::cout<<"Invalid input!"<<std::endl;
                std::cin.ignore();
                std::cout<<"Press enter to continue...";
                std::cin.ignore();
                break;
            case 2:
                std::cout<<"YOU WON!!!"<<std::endl;
                std::cout<<"Do you want to play again? y/n: ";
                std::cin>>choice;
                if(choice == 'n')
                {
                    game_on = false;
                }
                break;
            default:
                continue;
        }
    }
}