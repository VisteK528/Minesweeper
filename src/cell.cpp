#include "cell.hpp"

Cell::Cell(int x, int y, int value)
{
    setX(x);
    setY(y);
    this->value = value;
}

void Cell::setX(int x)
{
    if(x < 0)
    {
        throw InvalidPositionError("X position have to be greater than 0!");
    }
    else
    {
        this->x = x;
    }
}

void Cell::setY(int y)
{
    if(y < 0)
    {
        throw InvalidPositionError("Y position have to be greater than 0!");
    }
    else
    {
        this->y = y;
    }
}

void Cell::setValue(int value)
{
    this->value = value;
}

int Cell::getX()
{
    return x;
}

int Cell::getY()
{
    return y;
}

int Cell::getValue()
{
    return value;
}