//
// Created by piotr on 4/29/23.
//

#ifndef MINESWEEPER_MENU_HPP
#define MINESWEEPER_MENU_HPP

#include "widgets.hpp"
#include "state.hpp"

class Menu: public State{
private:
    std::unique_ptr<ui::Text> title;
    std::unique_ptr<ui::Button> start;
    std::unique_ptr<ui::Button> exit;
    sf::Font font;

    void initVariables();
public:
    Menu(std::shared_ptr<sf::RenderWindow> window, sf::Font &font);

    void init(){};
    virtual void updateKeybinds();
    virtual void update();
    virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);
};


#endif //MINESWEEPER_MENU_HPP
