#ifndef MINESWEEPER_MENU_HPP
#define MINESWEEPER_MENU_HPP

#include "../widgets.hpp"
#include "state.hpp"
#include "board_select_state.hpp"

class Menu: public State{
private:
    std::unique_ptr<ui::Text> title;
    std::unique_ptr<ui::Button> start;
    std::unique_ptr<ui::Button> exit;
    sf::Font font;

    sf::Image background;
    sf::Texture background_texture;
    sf::RectangleShape background_rectangle;

    void initVariables();
public:
    Menu(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, sf::Font &font);

    void init() override {};
    void update() override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
};


#endif //MINESWEEPER_MENU_HPP
