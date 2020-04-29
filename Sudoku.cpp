#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>

class Sudoku
{
    private:
        typedef std::vector<int> rad;
        typedef std::vector<rad> matrix;
        matrix grid;

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


public:

    Sudoku(int size = 9): grid(size, rad(size, 0))
    {
        for (int i = 0; i < 17; i++)
        {
            int x = randomNumber(0, 8);
            int y = randomNumber(0, 8);

            while( grid[y][x] != 0 )
            {
                x = randomNumber(0, 8);
                y = randomNumber(0, 8);
            }

            int n = randomNumber(1, 9);
            while( !possible(x, y, n) )
            {
                n = randomNumber(1, 9);
            }

            grid[y][x] = n;
            
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
                if ( grid[y][x] == 0)
                {
                    for(int n = 1; n < 10; n++)
                    {
                        if (possible(x, y, n))
                        {

                            grid[y][x] = n;
                            if (solve())
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

                
                if(rowCount == 3)
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

    // Can maybe be used for something.
    // Was a early try to create a function that generates the Sudoku Board
    /*
        std::vector<std::vector<int>> shuffleMatrix(std::vector<std::vector<int>> &vector)
        {
            static std::random_device rd;
            std::mt19937 g(rd());

            std::shuffle(vector.begin(), vector.end(), g);

            return vector;
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
        return n ;
    }

    // Checking if a number between 1-9 is allowed to be on a posistion of the matrix
    bool possible(const int &x, const int &y, const int &n)
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
};