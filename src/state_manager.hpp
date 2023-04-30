//
// Created by piotr on 4/29/23.
//

#ifndef MINESWEEPER_STATE_MANAGER_HPP
#define MINESWEEPER_STATE_MANAGER_HPP

#include <stack>
#include <SFML/Graphics.hpp>
#include <memory>
#include "state.hpp"
#include "menu.hpp"
#include "game_state.hpp"

class GameState;

class StateManager {
private:
    std::stack<std::unique_ptr<State>> states;
    std::shared_ptr<sf::RenderWindow> window;
    std::unique_ptr<sf::View> view;
    sf::Event e;
    sf::Font font;

    void pushState(std::unique_ptr<State> state);
    void popState();
    /*void changeState(std::unique_ptr<State> state);
    std::unique_ptr<State> peekState();*/

public:
    StateManager();
    ~StateManager();
    void updateSFMLEvents();
    void update();
    void render();
    void run();

};


#endif //MINESWEEPER_STATE_MANAGER_HPP
