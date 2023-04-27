#include "game.hpp"


Game::Game(int rows, int columns, int mines)
{
    this->moves = 0;
    this->rows = rows;
    this->columns = columns;
    this->mines = mines;
    this->board = Board(columns, rows, mines);
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{
    window->~RenderWindow();
    window.~unique_ptr();
}

void Game::initVariables()
{
    this->window = nullptr;
    width_ratio = (float)width/height;
    height_ratio = (float)height/width;
    tile_size = board_width/columns;
    position_size = tile_size;
    board_ratio = {(double)board_width/(double)width, (double)board_height/(double)height};
}

void Game::initWindow()
{
    this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Minesweeper");
    window->setKeyRepeatEnabled(false);
}


void Game::renderSprites()
{
    for(auto row: board_sprites)
    {
        for(auto sprite: row)
        {
            window->draw(*sprite);
        }
    }
}

void Game::loadTextures()
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

void Game::updateBoard()
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
            case 88:
                row.push_back(std::make_shared<sf::Sprite>(*textures[0]));
                break;
            case 70:
                row.push_back(std::make_shared<sf::Sprite>(*textures[4]));
                break;
            case 63:
                row.push_back(std::make_shared<sf::Sprite>(*textures[5]));
                break;
            case 87:
                row.push_back(std::make_shared<sf::Sprite>(*textures[8]));
                break;
            case 111:
                row.push_back(std::make_shared<sf::Sprite>(*textures[10]));
                break;
            case 73:
                row.push_back(std::make_shared<sf::Sprite>(*textures[9]));
                break;
            case 0:
                row.push_back(std::make_shared<sf::Sprite>(*textures[11]));
                break;

            case 9:
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

void Game::runGraphics()
{
    RESULTS result = CARRY_ON;
    updateBoard();
    window->setFramerateLimit(60);
    view = std::make_unique<sf::View>(window->getDefaultView());

    Text duration_text("Time elapsed: 00:00", font, 18, sf::Color::Yellow, sf::Vector2f(810.f, 50.f));
    Text mines_text("Mines: 0/"+std::to_string(mines), font, 25, sf::Color::Blue, sf::Vector2f(810.f, 10.f));

    while(window->isOpen())
    {
        sf::Event e;
        while(window->pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window->close();

            //Resizing the window
            else if(e.type == sf::Event::Resized)
            {
                sf::Vector2f view_size = { static_cast<float>(e.size.width), static_cast<float>(e.size.height)};
                view->setSize(view_size);
                window->setView(*view);
                sf::Vector2f size = view->getSize();

                board_width = board_ratio.first*size.x;
                board_height = board_ratio.second*size.y;

                position_size = std::min(board_ratio.first*size.x/columns, board_ratio.second*size.y/rows);
                updateBoard();

                /*duration_text.setPosition(window->mapPixelToCoords(sf::Vector2i{point+10, 50}, window->getView()));
                mines_text.setPosition(window->mapPixelToCoords(sf::Vector2i{point+10, 10}, window->getView()));*/
            }

            else if(e.type == sf::Event::MouseButtonReleased)
            {
                moves++;
                sf::Vector2i position = sf::Mouse::getPosition(*window);
                int column_pos = (int)(position.x/position_size);
                int row_pos = (int)(position.y/position_size);
                if(0 <= column_pos && column_pos < columns && 0 <= row_pos && row_pos < rows)
                {
                    if(e.mouseButton.button == sf::Mouse::Left)
                    {
                        if(moves == 1)
                        {
                            start = std::chrono::high_resolution_clock::now();
                        }
                        result = board.make_move(column_pos, row_pos, '1');
                    }
                    else if(e.mouseButton.button == sf::Mouse::Right)
                    {
                        result = board.make_move(column_pos, row_pos, 'F');
                        mines_text.setString("Mines: "+std::to_string(board.getFlaggedMines())+'/'+std::to_string(mines));
                    }
                }
                updateBoard();
                board.display_board(0);
            }
        }
        if(game_on && moves != 0)
        {
            stop = std::chrono::high_resolution_clock::now();
            duration_m = std::chrono::duration_cast<std::chrono::minutes>(stop-start);
            duration_s = std::chrono::duration_cast<std::chrono::seconds>(stop-start);
            std::stringstream stream;
            int seconds = duration_s.count()-duration_m.count()*60;
            stream<<"Time: "<<std::setw(2)<<std::setfill('0')<<std::to_string(duration_m.count())<<':'<<std::setw(2)<<std::setfill('0')<<std::to_string(seconds);
            duration_text.setString(stream.str());

        }

        // Rendering textures
        window->clear();
        renderSprites();
        window->draw(mines_text);
        window->draw(duration_text);
        window->display();

        char choice;
        switch(result)
        {
            case GAME_OVER:
                std::cout<<"Game over!"<<std::endl;
                std::cout<<"Do you want to play again? y/n: ";
                std::cin>>choice;
                if(choice == 'n')
                {
                    game_on = false;
                }
                else
                {
                    board.load_board_with_random_values(mines);
                    updateBoard();
                    moves = 0;
                }
                result = CARRY_ON;
                break;
            case INVALID_INPUT:
                std::cout<<"Invalid input!"<<std::endl;
                std::cin.ignore();
                std::cout<<"Press enter to continue...";
                std::cin.ignore();
                result = CARRY_ON;
                break;
            case WIN:
                std::cout<<"YOU WON!!!"<<std::endl;
                std::cout<<"Do you want to play again? y/n: ";
                std::cin>>choice;
                if(choice == 'n')
                {
                    game_on = false;
                }
                else
                {
                    board.load_board_with_random_values(mines);
                    updateBoard();
                    moves = 0;
                }
                result = CARRY_ON;
                break;
            default:
                break;
        }
        if(!game_on)
        {
            break;
        }
    }
}

void Game::runGame()
{
    loadTextures();
    runGraphics();
}

void Game::run()
{
    std::cout<<"Welcome to Mines!"<<std::endl;
    int result;
    while(game_on)
    {
        std::system("clear");
        board.display_board(0);
        int row = 0;
        int column = 0;
        char move;
        std::cout<<"Row: ";
        std::cin>>row;
        std::cout<<"Column: ";
        std::cin>>column;
        std::cout<<"Move: ";
        std::cin>>move;
        std::cout<<std::endl;
        std::cout<<std::endl;
        result = board.make_move(column, row, move);
        std::system("clear");
        board.display_board(0);
        std::cout<<std::endl;
        char choice;
        switch(result)
        {
            case 1:
                std::cout<<"Game over!"<<std::endl;
                std::cout<<"Do you want to play again? y/n: ";
                std::cin>>choice;
                if(choice == 'n')
                {
                    game_on = false;
                }
                else
                {
                    board.load_board_with_random_values(mines);
                }
                break;
            case 5:
                std::cout<<"Invalid input!"<<std::endl;
                std::cin.ignore();
                std::cout<<"Press enter to continue...";
                std::cin.ignore();
                break;
            case 2:
                std::cout<<"YOU WON!!!"<<std::endl;
                std::cout<<"Do you want to play again? y/n: ";
                std::cin>>choice;
                if(choice == 'n')
                {
                    game_on = false;
                }
                break;
            default:
                continue;
        }
    }
}