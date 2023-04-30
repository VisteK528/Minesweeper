#include <iostream>
#include "src/game.hpp"
#include "src/state_manager.hpp"
int main()
{
    /*Game game(20, 20, 40);
    game.runGame();*/
    StateManager manager;
    manager.run();
    return 0;
}