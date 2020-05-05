#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>

class Sudoku
{
private:
    // A vector that we call rows. Then we create a vector with n rows.
    typedef std::vector<int> row;
    typedef std::vector<row> matrix;
    matrix grid;

    matrix testBoard{
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},

        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},

        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

public:
    Sudoku(int size = 9) : grid(size, row(size, 0))
    {
        for (int i = 0; i < 17; i++)
        {
            int x = randomNumber(0, 8);
            int y = randomNumber(0, 8);

            while (grid[x][y] != 0)
            {
                x = randomNumber(0, 8);
                y = randomNumber(0, 8);
            }

            int n = randomNumber(1, 9);
            while (!possible(x, y, n))
            {
                n = randomNumber(1, 9);
            }

            grid[x][y] = n;
        }
    }

    // Recursive function that solves the board.
    bool solve()
    {
        for (int y = 0; y < 9; y++)
        {
            for (int x = 0; x < 9; x++)
            {
                // std::cout << "checking " << x << ", " << y << std::endl;
                if (grid[x][y] == 0)
                {
                    for (int n = 1; n < 10; n++)
                    {
                        if (possible(x, y, n))
                        {

                            grid[x][y] = n;
                            if (solve())
                            {
                                return true;
                            }
                            else
                            {
                                grid[x][y] = 0;
                            }
                        }
                    }

                    return false;
                }
            }
        }
        return true;
    }

    // Displays the grid in a sudoku board layout
    void display()
    {
        int rowCount = 0;
        int txtCount = 0;
        for (auto y : grid)
        {

            if (txtCount == 3)
            {
                std::cout << "\n";
                txtCount = 0;
            }
            txtCount++;
            for (auto n : y)
            {

                if (rowCount == 3)
                {
                    rowCount = 0;

                    std::cout << "  ";
                }
                rowCount++;

                std::cout << (n > 0 ? std::to_string(n) : "_") << " ";
            }
            std::cout << std::endl;

            rowCount = 0;
        }
        std::cout << std::endl;
    }

    // Clearing the whole grid, setting every postition in the array to 0
    matrix emptyGrid()
    {

        for (int y = 0; y < 9; y++)
        {
            for (int x = 0; x < 9; x++)
            {

                grid[x][y] = 0;
            }
        }
        return grid;
    }

    matrix getGrid()
    {
        return grid;
    }

    // Can maybe be used for something.
    // Was a early try to create a function that generates the Sudoku Board
    /*
        matrix shuffleMatrix()
        {
            static std::random_device rd;
            std::mt19937 g(rd());

            std::shuffle(grid.begin(), grid.end(), g);

            return grid;
        }
    */

private:
    static int randomNumber(int min, int max)
    {
        static std::random_device rd;
        static std::mt19937 eng(rd());
        std::uniform_int_distribution<int> distribution(min, max);
        auto n = distribution(eng);
        // Check n
        //std::cout << "randomNumber("<<min<<","<<max<<") = " << n << std::endl;
        return n;
    }

    // Checking if a number between 1-9 is allowed to be on a posistion of the matrix
    bool possible(const int &x, const int &y, const int &n)
    {

        // Check if n is at (x,i) then return false (ROW)
        for (int i = 0; i < 9; i++)
        {
            if (grid[x][i] == n)
            {
                return false;
            }
        }

        // Check if n is at (i, y) then return false (Collumn)
        for (int i = 0; i < 9; i++)
        {
            if (grid[i][y] == n)
            {
                return false;
            }
        }

        int x0 = (x / 3) * 3;
        int y0 = (y / 3) * 3;

        // Check the grid in a 3*3 box if n is in position then return false
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[x0 + i][y0 + j] == n)
                {
                    return false;
                }
            }
        }

        // Return True if the slot is possible.
        return true;
    }
};