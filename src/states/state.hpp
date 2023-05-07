#ifndef MINESWEEPER_STATE_HPP
#define MINESWEEPER_STATE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <map>
#include <memory>

class State {
protected:
    std::shared_ptr<std::stack<std::unique_ptr<State>>> states;
    std::shared_ptr<sf::RenderWindow> window;
    std::pair<double, double> change_ratio = {1, 1};
    bool quit;

    virtual void updateStateDimensions();
public:
    State(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::stack<std::unique_ptr<State>>> states);
    virtual ~State();

    virtual void init() = 0;
    virtual void handleEvent(const sf::Event& e) = 0;
    const bool& getQuit() const;
    virtual void update() = 0;
    virtual void render(std::shared_ptr<sf::RenderTarget> target) = 0;
};


#endif //MINESWEEPER_STATE_HPP
