#ifndef CELL_HPP
#define CELL_HPP

class Cell
{
private:
    int x;
    int y;
    int value;
public:
    Cell(int x, int y, int value);
    int get_x();
    int get_y();
    int get_value();
    void set_x(int x);
    void set_y(int y);
    void set_value(int value);
};

#endif