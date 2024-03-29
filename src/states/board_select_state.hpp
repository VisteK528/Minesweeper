#ifndef MINESWEEPER_BOARD_SELECT_STATE_HPP
#define MINESWEEPER_BOARD_SELECT_STATE_HPP

#include "../gui_manager.hpp"
#include "state.hpp"
#include "game_state.hpp"
#include "custom_board_state.hpp"

class BoardSelectState: public State{
private:
    std::unique_ptr<ui::Text> title;
    std::unique_ptr<ui::Button> easy;
    std::unique_ptr<ui::Button> medium;
    std::unique_ptr<ui::Button> hard;
    std::unique_ptr<ui::Button> custom;
    std::unique_ptr<ui::Button> back;

    std::shared_ptr<GuiManager> gui_manager;

    sf::Image background;
    sf::Texture background_texture;
    sf::RectangleShape background_rectangle;

    void initVariables();
public:
    BoardSelectState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, std::shared_ptr<GuiManager> gui_manager);

    void init() override {};
    void update() override;
    void handleEvent(const sf::Event& e) override;
    void render(std::shared_ptr<sf::RenderTarget> target) override;
};

#endif //MINESWEEPER_BOARD_SELECT_STATE_HPP
