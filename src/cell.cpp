#include "cell.hpp"

Cell::Cell(int x, int y, int value)
{
    this->x = x;
    this->y = y;
    this->value = value;
}

void Cell::set_x(int x)
{
    this->x = x;
}

void Cell::set_y(int y)
{
    this->y = y;
}

void Cell::set_value(int value)
{
    this->value = value;
}

int Cell::get_x()
{
    return x;
}

int Cell::get_y()
{
    return y;
}

int Cell::get_value()
{
    return value;
}