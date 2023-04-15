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
}

void Game::initWindow()
{
    this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width+250, height), "Minesweeper");
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
    for(unsigned int i=0; i<5; i++)
    {
        for(unsigned int j=0; j<4; j++)
        {
            textures.push_back(std::make_shared<sf::Texture>());
            (textures[textures.size()-1])->loadFromFile("textures/textures.png", sf::IntRect(j*tile_texture_size.first,i*tile_texture_size.second, tile_texture_size.first, tile_texture_size.second));
        }
    }
}

void Game::updateBoard()
{
    // Load board
    auto my_board = board.getBoard();
    float tile_size = width/columns;

    for(int i = 0; i<rows; i++)
    {
        std::vector<std::shared_ptr<sf::Sprite>> row;
        for(int j =0; j<columns; j++)
        {
            unsigned int value = my_board[j][i].getMaskedValue();
            switch (value)
            {
            case 88:
                row.push_back(std::make_shared<sf::Sprite>(*textures[0]));
                break;
            case 70:
                row.push_back(std::make_shared<sf::Sprite>(*textures[4]));
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
            row[row.size()-1]->setPosition(i*tile_size, j*tile_size);
            row[row.size()-1]->setScale(tile_size/tile_texture_size.first, tile_size/tile_texture_size.second);

        }
        board_sprites.push_back(row);
    }
}

void Game::runGraphics()
{
    float tile_size = width/columns;
    unsigned int result;
    updateBoard();
    window->setFramerateLimit(30);

    sf::Font font;
    font.loadFromFile("textures/Arial.ttf");
    sf::Text duration_text;
    sf::Text mines_text;

    mines_text.setCharacterSize(25);
    mines_text.setFillColor(sf::Color::Red);
    mines_text.setString("Mines: 0/"+std::to_string(mines));
    mines_text.setPosition(810.f, 10.f);
    mines_text.setFont(font);

    duration_text.setCharacterSize(20);
    duration_text.setFillColor(sf::Color::Yellow);
    duration_text.setString("Time elapsed: 00:00");
    duration_text.setPosition(810.f, 50.f);
    duration_text.setFont(font);

    while(window->isOpen())
    {
        window->clear();
        sf::Event e;
        while(window->pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window->close();

            if(e.type == sf::Event::MouseButtonReleased)
            {
                moves++;
                sf::Vector2i position = sf::Mouse::getPosition(*window);
                int column_pos = (int)(position.x/tile_size);
                int row_pos = (int)(position.y/tile_size);
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
                updateBoard();
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
        renderSprites();
        window->draw(mines_text);
        window->draw(duration_text);
        window->display();

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
                    updateBoard();
                    moves = 0;
                }
                result = 0;
                break;
            case 5:
                std::cout<<"Invalid input!"<<std::endl;
                std::cin.ignore();
                std::cout<<"Press enter to continue...";
                std::cin.ignore();
                result = 0;
                break;
            case 2:
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
                result = 0;
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