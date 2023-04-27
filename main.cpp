#include <iostream>
#include "src/game.hpp"
#include "src/interface.hpp"

int main()
{
    /*Game game(20, 20, 40);
    game.runGame();*/
    Interface interface;
    while(interface.isAlive()){
        interface.update();
    }
    return 0;
}