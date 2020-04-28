#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>  
#include <algorithm>
#include <random>
#include <iterator>

typedef std::vector<int> rad;
typedef std::vector<rad> matrix;

int randomNumber(int min, int max);
matrix shuffleMatrix(std::vector<std::vector<int>> &vector);
matrix generateGrid();
void displayVector(const std::vector<std::vector<int>> &grid);
bool possible(const int & x, const int & y, const int & n, const std::vector<std::vector<int>> &grid);
bool solve(std::vector<std::vector<int>> &grid);


int randomNumber(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 eng(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    auto n = distribution(eng);
        // Check n
        //std::cout << "randomNumber("<<min<<","<<max<<") = " << n << std::endl;
    return n ;
}


matrix shuffleMatrix(matrix &vector)
{
    static std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(vector.begin(), vector.end(), g);

    return vector;
}


// Generate the soduko board ( W.I.P )
matrix generateGrid()
{
    int size = 9;
    
    matrix soduko(size, rad(size, 0));

    for (int i = 0; i < 17; i++)
    {
        int x = randomNumber(0, 8);
        int y = randomNumber(0, 8);

        while( soduko[y][x] != 0 )
        {
            x = randomNumber(0, 8);
            y = randomNumber(0, 8);
        }

        int n = randomNumber(1, 9);
        while( !possible(x, y, n, soduko) )
        {
            n = randomNumber(1, 9);
        }

        soduko[y][x] = n;
        
    }
    
    return soduko;
}

// Display a Vector in Grid / Matrix format
void displayVector(const matrix &grid)
{
    int rowCount = 1;
    for (auto y : grid)
    {
        for (auto n : y)
        {
            std::cout << (n > 0 ? std::to_string(n) : "_") << " ";

        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
}
// Checking if a number between 1-9 is allowed to be on a posistion of the matrix
bool possible(const int &x, const int &y, const int &n, const matrix &grid)
{

    for (int i = 0; i < 9; i++)
    {
        if (grid[y][i] == n)
        {
            return false;
        }
    }

    for (int i = 0; i < 9; i++)
    {
        if (grid[i][x] == n)
        {
            return false;
        }
    }

    int x0 = (x/3) * 3;
    int y0 = (y/3) * 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[y0 + i][x0 + j] == n)
            {
                return false;
            }
        }
    }

    return true;
    
}

// Recursive function that solves the Matrix.
bool solve(matrix &grid)
{
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            // std::cout << "checking " << x << ", " << y << std::endl;
            if ( grid[y][x] == 0)
            {
                for(int n = 1; n < 10; n++)
                {
                    if (possible(x, y, n, grid))
                    {

                        grid[y][x] = n;
                        if (solve(grid))
                        {
                            return true;
                        }
                        else
                        {
                            grid[y][x] = 0;                            
                        }


                    } 

                }

                return false;
            }

        }
        
    }
    return true;

}

int main()
{

    matrix testBoard 
    {
        {5, 3, 0,   0, 7, 0,   0, 0, 0}, 
        {6, 0, 0,   1, 9, 5,   0, 0, 0}, 
        {0, 9, 8,   0, 0, 0,   0, 6, 0}, 

        {8, 0, 0,   0, 6, 0,   0, 0, 3}, 
        {4, 0, 0,   8, 0, 3,   0, 0, 1}, 
        {7, 0, 0,   0, 2, 0,   0, 0, 6}, 

        {0, 6, 0,   0, 0, 0,   2, 8, 0}, 
        {0, 0, 0,   4, 1, 9,   0, 0, 5}, 
        {0, 0, 0,   0, 8, 0,   0, 7, 9}
    };

    // std::cout << solve(grid) << std::endl;
    matrix grid = generateGrid();

    // shuffleMatrix(testboard1);

    // displayVector(testboard1);
    
    std::cout << "Before solved: \n";
    displayVector(grid);
    
    if (solve(grid))
    {
        std::cout << "Solved: \n";
        displayVector(grid);
    }
    else
    {
        std::cout << "No solution.\n";
    }

    return 0;
}