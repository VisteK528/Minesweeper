//
// Created by piotr on 4/29/23.
//

#ifndef MINESWEEPER_GAME_HPP
#define MINESWEEPER_GAME_HPP

#include <stack>
#include <SFML/Graphics.hpp>
#include <memory>
#include "state.hpp"
#include "menu.hpp"
#include "game_state.hpp"
#include "board_select_state.hpp"


class Game {
private:
    std::shared_ptr<std::stack<std::unique_ptr<State>>> states;
    std::shared_ptr<sf::RenderWindow> window;
    std::unique_ptr<sf::View> view;
    sf::Event e;
    sf::Font font;

    unsigned int width = 1150;
    unsigned int height = 800;

    const sf::Vector2u min_dimensions = {575, 400};

    void pushState(std::unique_ptr<State> state);
    void updateSFMLEvents();
    void update();
    void render();

public:
    Game();
    ~Game();
    void run();

};


#endif //MINESWEEPER_GAME_HPP
