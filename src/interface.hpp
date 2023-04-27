#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "widgets.hpp"
#include <SFML/Graphics.hpp>
#include <memory>


class Interface
{
    private:
        std::unique_ptr<sf::RenderWindow> window;
        sf::Font font;
        std::unique_ptr<ui::Text> title;

        int window_width = 1150;
        int window_height = 800;
public:
    bool isAlive() const;
    void update();

private:

    void initVariables();
        void initWindow();

    public:
        Interface();
};

#endif