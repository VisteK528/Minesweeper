#include "game.hpp"

Game::Game() {
    // Setting SFML window and related things
    this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1150, 800), "Minesweeper");
    this->window->setFramerateLimit(120);
    this->view = std::make_unique<sf::View>(window->getDefaultView());

    // Loading textures and settting window icon
    loadTextures();
    setIcon();

    this->gui_manager = std::make_shared<GuiManager>(this->font, this->widget_background_color, this->widget_text_color);

    this->states = std::make_shared<std::stack<std::unique_ptr<State>>>();
    pushState(std::make_unique<Menu>(this->window, this->states, this->gui_manager));
    this->states->top()->init();
}

Game::~Game() {
    while(!this->states->empty()){
        states->pop();
    }
}
void Game::pushState(std::unique_ptr<State> state) {
    this->states->push(std::move(state));
}

void Game::render() {
    this->window->clear();
    if(!this->states->empty()){
        this->states->top()->render(this->window);
    }
    this->window->display();
}

void Game::update() {
    updateSFMLEvents();
    if(!this->states->empty()){
        this->states->top()->update();
        if(this->states->top()->getQuit()){
            this->states->pop();
            if(!this->states->empty()){
                this->states->top()->init();
            }
        }
    }
    else{
        window->close();
    }
}

void Game::updateSFMLEvents() {
    while(this->window->pollEvent(e)){
        if(this->e.type == sf::Event::Closed){
            this->window->close();
        }
        else if(this->e.type == sf::Event::Resized) {
            sf::Vector2f view_size = {static_cast<float>(this->e.size.width), static_cast<float>(this->e.size.height)};
            view->setSize(view_size);
            window->setView(*view);
            if(view_size.x < min_dimensions.x || view_size.y < min_dimensions.y){
                window->setSize(min_dimensions);
            }
        }
        if(!this->states->empty()){
            this->states->top()->handleEvent(e);
        }
    }
}

void Game::run() {
    while(this->window->isOpen()){
        update();
        render();
    }
}

void Game::loadTextures() {
    if(!this->app_icon_texture.loadFromFile("textures/textures.png", sf::IntRect(0, 1024, 512, 512))){
        throw TexturesLoadingError("Cannot load window icon!");
    }

    if(!this->font.loadFromFile("textures/mine-sweeper.ttf")){
        throw TexturesLoadingError("Cannot load default font from file textures/mine-sweeper.ttf");
    }
    widget_background_color = {sf::Color(80,80,80), sf::Color(120,120,120)};
    widget_text_color = {sf::Color::White, sf::Color::White};
}

void Game::setIcon(){
    sf::Image image = app_icon_texture.copyToImage();
    this->window->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}