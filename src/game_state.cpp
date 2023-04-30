//
// Created by piotr on 4/29/23.
//

#include "game_state.hpp"

GameState::GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, int rows, int columns, int mines): State(window, states){
    this->moves = 0;
    this->rows = rows;
    this->columns = columns;
    this->mines = mines;
    this->mines_info = nullptr;
    this->time_info = nullptr;
    this->play_again_btn = nullptr;
    this->change_difficulty_btn = nullptr;
    this->pause_btn = nullptr;


    this->board = Board(rows, columns, mines);
    this->initVariables();
}

void GameState::initVariables()
{
    position_size = std::min(board_width/columns, board_height/rows);
    board_ratio = {(double)board_width/(double)width, (double)board_height/(double)height};

    if(columns > rows){
        offset.y = (board_height - rows*position_size)/2;
    }
    else if(rows > columns){
        offset.x = (board_width - columns*position_size)/2;
    }
}

void GameState::renderSprites()
{
    for(auto row: board_sprites)
    {
        for(auto sprite: row)
        {
            window->draw(*sprite);
        }
    }
}

void GameState::loadTextures()
{
    // Load texturemap
    if(!image.loadFromFile("textures/textures.png"))
    {
        throw TexturesLoadingError("Unable to load textures!");
    }

    if(!font.loadFromFile("textures/mine-sweeper.ttf"))
    {
        throw FontLoadingError("Unable to load font!");
    }

    for(unsigned int i=0; i<5; i++)
    {
        for(unsigned int j=0; j<4; j++)
        {
            textures.push_back(std::make_shared<sf::Texture>());
            (textures[textures.size()-1])->loadFromImage(image, sf::IntRect(j*tile_texture_size.first,i*tile_texture_size.second, tile_texture_size.first, tile_texture_size.second));
        }
    }
}

void GameState::init() {
    loadTextures();
    std::pair<sf::Color, sf::Color> background_color = {sf::Color::Blue, sf::Color::Transparent};
    std::pair<sf::Color, sf::Color> text_color = {sf::Color::White, sf::Color::Red};

    this->time_info = std::make_unique<ui::Text>("Time: 00:00", font, 18, sf::Color::Yellow, sf::Vector2f(810.f, 50.f));
    this->mines_info = std::make_unique<ui::Text>("Mines: 0/"+std::to_string(mines), font, 25, sf::Color::Blue, sf::Vector2f(810.f, 10.f));

    this->play_again_btn = std::make_unique<ui::Button>("> Start over", font, 15, background_color, text_color, sf::Vector2f(810, 500), sf::Vector2f(200, 50), ui::ORIGIN::NW);
    this->change_difficulty_btn = std::make_unique<ui::Button>("> Change difficulty", this->font, 15, background_color, text_color, sf::Vector2f(810, 575), sf::Vector2f(300, 50), ui::ORIGIN::NW);
    //this->pause_btn = std::make_unique<ui::Button>("> Pause", this->font, 15, background_color, text_color, sf::Vector2f(810, 650), sf::Vector2f(200, 50), ui::ORIGIN::NW);
    //this->pause_btn->setActive(false);
    updateBoard();
}

void GameState::updateBoard()
{
    // Load board
    auto my_board = board.getBoard();
    board_sprites.clear();
    for(int i = 0; i<rows; i++)
    {
        std::vector<std::shared_ptr<sf::Sprite>> row;
        for(int j = 0; j<columns; j++)
        {
            unsigned int value = my_board[i][j].getMaskedValue();
            switch (value)
            {
                case COVERED:
                    row.push_back(std::make_shared<sf::Sprite>(*textures[0]));
                    break;
                case FLAGGED:
                    row.push_back(std::make_shared<sf::Sprite>(*textures[4]));
                    break;
                case QUESTION:
                    row.push_back(std::make_shared<sf::Sprite>(*textures[5]));
                    break;
                case OTHER_EXPLODED:
                    row.push_back(std::make_shared<sf::Sprite>(*textures[8]));
                    break;
                case EXPLODED:
                    row.push_back(std::make_shared<sf::Sprite>(*textures[10]));
                    break;
                case INVALIDLY_FLAGGED:
                    row.push_back(std::make_shared<sf::Sprite>(*textures[9]));
                    break;
                case EMPTY:
                    row.push_back(std::make_shared<sf::Sprite>(*textures[11]));
                    break;
                case MINE:
                    row.push_back(std::make_shared<sf::Sprite>(*textures[8]));
                    break;
                default:
                    row.push_back(std::make_shared<sf::Sprite>(*textures[value+11]));
            }
            row[row.size()-1]->setOrigin(0, 0);
            row[row.size()-1]->setPosition(window->mapPixelToCoords(sf::Vector2i{offset.x+(int)(j*position_size), offset.y+(int)(i*position_size)}, window->getView()));
            row[row.size()-1]->setScale(position_size/tile_texture_size.first, position_size/tile_texture_size.second);

        }
        board_sprites.push_back(row);
    }
}

void GameState::update() {
    sf::Vector2f size = this->window->getView().getSize();

    board_width = board_ratio.first * size.x;
    board_height = board_ratio.second * size.y;
    position_size = std::min(board_ratio.first * size.x / columns, board_ratio.second * size.y / rows);

    sf::Vector2i position = sf::Mouse::getPosition(*window);
    sf::Vector2i mouse_board_coords = {int((position.x-offset.x)/position_size), int((position.y-offset.y)/position_size)};

    if(0 <= mouse_board_coords.x && mouse_board_coords.x < columns && 0 <= mouse_board_coords.y && mouse_board_coords.y < rows && game_on)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if(!button_left_pressed){
                moves++;
                button_left_pressed = true;
                button_right_pressed = false;
                if(moves == 1)
                {
                    start = std::chrono::high_resolution_clock::now();
                }
                result = board.makeMove(mouse_board_coords.x, mouse_board_coords.y, UNCOVER);
            }

        }
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            if(!button_right_pressed){
                button_left_pressed = false;
                button_right_pressed = true;
                result = board.makeMove(mouse_board_coords.x, mouse_board_coords.y, FLAG);
                mines_info->setString("Mines: "+std::to_string(board.getFlaggedMines())+'/'+std::to_string(mines));
            }
        }
        else {
            button_left_pressed = false;
            button_right_pressed = false;
        }
    }
    if(result != CARRY_ON){
        game_on = false;
        this->play_again_btn->setText("> Play again");
    }
    updateBoard();

    if(game_on && moves != 0)
    {
        stop = std::chrono::high_resolution_clock::now();
        duration_m = std::chrono::duration_cast<std::chrono::minutes>(stop-start);
        duration_s = std::chrono::duration_cast<std::chrono::seconds>(stop-start);
        std::stringstream stream;
        int seconds = duration_s.count()-duration_m.count()*60;
        stream<<"Time: "<<std::setw(2)<<std::setfill('0')<<std::to_string(duration_m.count())<<':'<<std::setw(2)<<std::setfill('0')<<std::to_string(seconds);
        time_info->setString(stream.str());

    }

    //Relative position after view change
    sf::Vector2f corrected_position = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), window->getView());

    if(this->play_again_btn->update(corrected_position)){
        restart();
    }
    if(this->change_difficulty_btn->update(corrected_position)){
        quit = true;
    }

    /*if(this->pause_btn->update(corrected_position)){
        if(game_on){
            game_on = false;
            this->pause_btn->setText("> Resume");
        }
        else{
            game_on = true;
            this->pause_btn->setText("> Pause");
        }
    }*/

}

void GameState::restart() {
    result = RESULTS::CARRY_ON;
    this->time_info->setString("Time: 00:00");
    this->mines_info->setString("Mines: 0/"+std::to_string(mines));
    this->play_again_btn->setText("> Start over");
    //this->pause_btn->setText("> Pause");
    game_on = true;
    moves = 0;
    board.loadBoardWithRandomValues(mines);
}

void GameState::render(std::shared_ptr<sf::RenderTarget> target) {
    renderSprites();
    target->draw(*time_info);
    target->draw(*mines_info);
    target->draw(*change_difficulty_btn);
    target->draw(*play_again_btn);
    //target->draw(*pause_btn);
}