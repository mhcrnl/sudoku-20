#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>

using namespace std;

void fancy_line();

class sudoku
{
public:
    sudoku();
    virtual ~sudoku();
    void draw();
    bool check_row(int row);
    bool check_col(int);
protected:

private:
    int grid[9][9];
};

#endif // SUDOKU_H
