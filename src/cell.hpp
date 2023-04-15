#ifndef CELL_HPP
#define CELL_HPP

#include <exception>
#include <string>

class Cell
{
private:
    int x;
    int y;
    int value;
    int masked_value;
public:
    Cell(int x, int y, int value);
    int getX() const;
    int getY() const;
    int getValue() const;
    int getMaskedValue() const;
    void setX(int x);
    void setY(int y);
    void setValue(int value);
    void setMaskedValue(int masked_value);
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