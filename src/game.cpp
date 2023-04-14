#include "game.hpp"


Game::Game(int rows, int columns, int mines)
{
    this->rows = rows;
    this->columns = columns;
    this->mines = mines;
    this->board = Board(columns, rows, mines);
    this->initVariables();
    this->initWindow();
}

void Game::initVariables()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    //this -> window = new sf::RenderWindow(sf::VideoMode(800, 800), "Minesweeper");
    this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 800), "Minesweeper");
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
            (textures[textures.size()-1])->loadFromFile("textures/textures.png", sf::IntRect(j*512,i*512, 512, 512));
        }
    }
}
void Game::updateBoard()
{
    // Load board
    auto my_board = board.getBoard();
    float tile_size = 800/columns;

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
            row[row.size()-1]->setScale(tile_size/512., tile_size/512.);

        }
        board_sprites.push_back(row);
    }
}

void Game::runGraphics()
{
    auto t1 = std::chrono::system_clock::now();
    updateBoard();
    auto t2 = std::chrono::system_clock::now();
    auto elapsed = t2-t1;
    //std::cout<<elapsed.count()<<std::endl;

    window->setFramerateLimit(120);
    while(window->isOpen())
    {
        sf::Event e;
        while(window->pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window->close();
        }
        renderSprites();
        window->display();
    }
}

void Game::runGame()
{
    loadTextures();
    std::thread graphics(&Game::runGraphics, this);
    std::thread input(&Game::run, this);

    input.join();
    graphics.~thread();
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
        renderSprites();
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