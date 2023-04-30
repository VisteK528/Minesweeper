//
// Created by piotr on 4/29/23.
//

#include "game_state.hpp"

GameState::GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states, int rows, int columns, int mines): State(window, states){
    this->moves = 0;
    this->rows = rows;
    this->columns = columns;
    this->mines = mines;

    this->board = Board(columns, rows, mines);
    this->initVariables();
}

void GameState::initVariables()
{
    tile_size = board_width/columns;
    position_size = tile_size;
    board_ratio = {(double)board_width/(double)width, (double)board_height/(double)height};
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
    std::pair<sf::Color, sf::Color> background_color = {sf::Color::Transparent, sf::Color::Transparent};
    std::pair<sf::Color, sf::Color> text_color = {sf::Color::White, sf::Color::Red};

    this->time_info = std::make_unique<ui::Text>("Time: 00:00", font, 18, sf::Color::Yellow, sf::Vector2f(810.f, 50.f));
    this->mines_info = std::make_unique<ui::Text>("Mines: 0/"+std::to_string(mines), font, 25, sf::Color::Blue, sf::Vector2f(810.f, 10.f));
    this->play_again = std::make_unique<ui::Button>("> Play again", this->font, 10, background_color, text_color, sf::Vector2f(810, 450), sf::Vector2f(200, 50), ui::ORIGIN::C);
    this->change_difficulty = std::make_unique<ui::Button>("> Change difficulty", this->font, 10, background_color, text_color, sf::Vector2f(810, 550), sf::Vector2f(200, 50), ui::ORIGIN::C);
    loadTextures();
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
                    row.push_back(std::make_shared<sf::Sprite>(*textures[value+11]));;
            }
            row[row.size()-1]->setOrigin(0, 0);
            row[row.size()-1]->setPosition(window->mapPixelToCoords(sf::Vector2i{(int)(j*position_size), (int)(i*position_size)}, window->getView()));
            row[row.size()-1]->setScale(position_size/tile_texture_size.first, position_size/tile_texture_size.second);

        }
        board_sprites.push_back(row);
    }
}

void GameState::update() {
    this->updateKeybinds();
    sf::Vector2f size = this->window->getView().getSize();

    board_width = board_ratio.first * size.x;
    board_height = board_ratio.second * size.y;
    position_size = std::min(board_ratio.first * size.x / columns, board_ratio.second * size.y / rows);

    sf::Vector2i position = sf::Mouse::getPosition(*window);
    int column_pos = (int)(position.x/position_size);
    int row_pos = (int)(position.y/position_size);
    if(0 <= column_pos && column_pos < columns && 0 <= row_pos && row_pos < rows && game_on)
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
                result = board.makeMove(column_pos, row_pos, UNCOVER);
            }

        }
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            if(!button_right_pressed){
                moves++;
                button_left_pressed = false;
                button_right_pressed = true;
                result = board.makeMove(column_pos, row_pos, FLAG);
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

    if(this->play_again->update(static_cast<sf::Vector2f>(position))){
        restart();
    }
    if(this->change_difficulty->update(static_cast<sf::Vector2f>(position))){
        quit = true;
    }

}

void GameState::restart() {
    result = RESULTS::CARRY_ON;
    this->time_info->setString("Time: 00:00");
    this->mines_info->setString("Mines: 0/"+std::to_string(mines));
    game_on = true;
    moves = 0;
    board.loadBoardWithRandomValues(mines);
}

void GameState::render(std::shared_ptr<sf::RenderTarget> target) {
    renderSprites();
    target->draw(*time_info);
    target->draw(*mines_info);
    target->draw(*change_difficulty);
    if(result != CARRY_ON){
        target->draw(*play_again);
    }

}

void GameState::updateKeybinds() {
    this->checkForQuit();
}