#include "cell.hpp"

Cell::Cell(int x, int y, int value)
{
    setX(x);
    setY(y);
    this->value = value;
    setMaskedValue('X');
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

void Cell::setMaskedValue(int masked_value)
{
    this->masked_value=masked_value;
}

int Cell::getX() const
{
    return x;
}

int Cell::getY() const
{
    return y;
}

int Cell::getValue() const
{
    return value;
}

int Cell::getMaskedValue() const
{
    return masked_value;
}