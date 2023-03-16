#ifndef CELL_HPP
#define CELL_HPP

#include <exception>
#include <string>

class Cell
{
private:
    unsigned int x;
    unsigned int y;
    int value;
public:
    Cell(int x, int y, int value);
    int getX();
    int getY();
    int getValue();
    void setX(int x);
    void setY(int y);
    void setValue(int value);
};

class InvalidPositionError: public std::exception
{
    private:
        std::string message;
    public:
        InvalidPositionError(const std::string &msg): message(msg){};
        const char* what() const noexcept {return message.c_str();}
};

#endif