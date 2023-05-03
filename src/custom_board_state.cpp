//
// Created by piotr on 5/2/23.
//

#include "custom_board_state.hpp"

CustomBoardState::CustomBoardState(std::shared_ptr<sf::RenderWindow> window,
                                   std::shared_ptr<std::stack<std::unique_ptr<State>>> states,
                                   sf::Font &font): State(window, states) {

    this->font = font;
    this->title = nullptr;
    this->rows_text = nullptr;
    this->columns_text = nullptr;
    this->mines_text = nullptr;

    this->rows_spinbox = nullptr;
    this->columns_spinbox = nullptr;
    this->mines_spinbox = nullptr;

    this->start_btn = nullptr;
    this->cancel_btn = nullptr;
    initVariables();
}

void CustomBoardState::initVariables() {
    this->background.loadFromFile("textures/menu_background.png");
    this->background_texture.loadFromImage(background);

    this->background_rectangle.setPosition(0,0);
    this->background_rectangle.setSize({1150, 800});
    this->background_rectangle.setTexture(&background_texture);
    this->background_rectangle.setFillColor(sf::Color(255, 255, 255, 180));

    this->title = std::make_unique<ui::Text>("Minesweeper", font, 40, sf::Color(255,255,255, 255), sf::Vector2f(50, 50), ui::ORIGIN::NW);
    this->rows_text = std::make_unique<ui::Text>("ROWS", font, 20, sf::Color(255,255,255, 255), sf::Vector2f(250, 300), ui::ORIGIN::NW);
    this->columns_text = std::make_unique<ui::Text>("COLUMNS", font, 20, sf::Color(255,255,255, 255), sf::Vector2f(250, 400), ui::ORIGIN::NW);
    this->mines_text = std::make_unique<ui::Text>("PERCENTAGE MINES", font, 20, sf::Color(255,255,255, 255), sf::Vector2f(250, 500), ui::ORIGIN::NW);

    std::pair<sf::Color, sf::Color> background_color = {sf::Color(80,80,80), sf::Color(120,120,120)};
    std::pair<sf::Color, sf::Color> text_color = {sf::Color::White, sf::Color::White};

    this->rows_spinbox = std::make_unique<ui::Spinbox>(this->font, 20, background_color, text_color, sf::Vector2f(700, 300), sf::Vector2f(200, 50), ui::ORIGIN::C, rows_range.first, rows_range.second, rows);
    this->columns_spinbox = std::make_unique<ui::Spinbox>(this->font, 20, background_color, text_color, sf::Vector2f(700, 400), sf::Vector2f(200, 50), ui::ORIGIN::C, columns_range.first, columns_range.second, columns);
    this->mines_spinbox = std::make_unique<ui::Spinbox>(this->font, 20, background_color, text_color, sf::Vector2f(700, 500), sf::Vector2f(200, 50), ui::ORIGIN::C, mines_percentage_range.first, mines_percentage_range.second, percentage_mines);

    std::pair<sf::Color, sf::Color> play_btn_background_clr = {sf::Color(0, 153, 0), sf::Color(0, 204, 0)};
    this->start_btn = std::make_unique<ui::Button>("Play Game", this->font, 20, play_btn_background_clr, text_color, sf::Vector2f(575, 600), sf::Vector2f(220, 60), ui::ORIGIN::C);
    this->cancel_btn = std::make_unique<ui::Button>("Cancel", this->font, 20, background_color, text_color, sf::Vector2f(575, 680), sf::Vector2f(200, 50), ui::ORIGIN::C);
}

void CustomBoardState::update() {
    sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());

    rows = rows_spinbox->update(position);
    columns = columns_spinbox->update(position);
    percentage_mines = mines_spinbox->update(position);

    if(start_btn->update(position)){
        quit = true;
        int mines = rows*columns*((float)percentage_mines/100);
        states->push(std::make_unique<GameState>(this->window, this->states, rows, columns, mines));
        states->top()->init();
    }
    if(cancel_btn->update(position)){
        quit = true;
    }
}

void CustomBoardState::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(this->background_rectangle);
    target->draw(*title);
    target->draw(*rows_text);
    target->draw(*columns_text);
    target->draw(*mines_text);

    target->draw(*rows_spinbox);
    target->draw(*columns_spinbox);
    target->draw(*mines_spinbox);

    target->draw(*start_btn);
    target->draw(*cancel_btn);

}