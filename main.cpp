#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>

#include "Sudoku.cpp"

// typedef std::vector<int> rad;
// typedef std::vector<rad> matrix;

int main()
{

    Sudoku s;

    std::cout << "Before solved: \n";
    s.display();

    if (s.solve())
    {
        std::cout << "Solved: \n";
        s.display();
    }
    else
    {
        std::cout << "No solution.\n";
    }

    return 0;
}