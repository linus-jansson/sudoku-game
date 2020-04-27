#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>  

typedef std::vector<int> rad;
typedef std::vector<rad> matrix;

matrix generateGrid();
void displayVector(const std::vector<std::vector<int>> & grid);
bool possible(const int & x, const int & y, const int & n, const std::vector<std::vector<int>> & grid);
bool solve(std::vector<std::vector<int>> & grid);

// void map(/*int size*/)
// {
//     int size = 9;
//     // int x, y;
//     typedef std::vector<int> rad;
//     typedef std::vector<rad> matrix;


//     matrix soduko(size,rad(size,(rand() % 9 + 1 )));
//     //int array[sizeX][sizeY] = {0};
    
    

//     for ( auto r : soduko )
//     {
//         for( auto n : r)
//         {

//             // if (array[x][y] == 0)
//             // {
//             //     array[x][y] = 1;
//             // }
//             std::cout << n << " ";

//         } 
//         std::cout << std::endl;
//     }

// }

// Generate the soduko board ( W.I.P )
matrix generateGrid()
{
    int size = 9;
    
    matrix soduko(size, rad(size, 0));

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            int n = rand() % 9 + 1 ;
            while( ! possible(x, y, n, soduko))
            {
                n = rand() % 9 + 1 ;
                // displayVector(soduko);
            }
            
            std::cout << x << "," << y << " done\n";

            soduko[y][x] =  n;
    
        }
        
    }

    return soduko;
}

// Display a Vector in Grid / Matrix format
void displayVector(const matrix &grid)
{
    for (auto y : grid)
    {
        for (auto n : y)
        {
            std::cout << n << " ";
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
bool solve(std::vector<std::vector<int>> & grid)
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
                        
                        // return;

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
    srand (time(NULL));

    std::vector<std::vector<int>> grid 
    {
        {5, 3, 0, 0, 7, 0, 0, 0, 0}, 
        {6, 0, 0, 1, 9, 5, 0, 0, 0}, 
        {0, 9, 8, 0, 0, 0, 0, 6, 0}, 
        {8, 0, 0, 0, 6, 0, 0, 0, 3}, 
        {4, 0, 0, 8, 0, 3, 0, 0, 1}, 
        {7, 0, 0, 0, 2, 0, 0, 0, 6}, 
        {0, 6, 0, 0, 0, 0, 2, 8, 0}, 
        {0, 0, 0, 4, 1, 9, 0, 0, 5}, 
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };


    
    // std::cout << solve(grid) << std::endl;

    // displayVector(grid);
    
    // if (solve(grid))
    // {
    //     displayVector(grid);
    // }
    // else
    // {
    //     std::cout << "No solution.\n";
    // }
    
    displayVector(generateGrid());
    
    // map();
    // std::cout << grid() << std::endl;

    return 0;
}