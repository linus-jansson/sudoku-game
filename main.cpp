#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>


#include "Sudoku.cpp"

// typedef std::vector<int> rad;
// typedef std::vector<rad> matrix;

void clear() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
}


int main()
{


    int menuOption;
    char option;
    bool running = true;
    bool editing;

    do
    {   
        // clear();
        std::cout << "What do you want to do?"
                  << "\n1. Generate a Sudoku board"
                //   << "\n2. Fill in empty board"
                  << "\n0. Exit\n";
        std::cin >> menuOption;

        Sudoku s;
        Sudoku copyBoard;
        copyBoard = s;

        switch (menuOption)
        {
        case 1:
                clear();
                std::cout << "Before solved: \n";
                s.display();

                std::cout << "Do you want to solve the board? Y or N\n";
                std::cin >> option;
                
                switch (option)
                {
                case 'Y':
                case 'y':
                    if (s.solve())
                    {
                        clear();
                        std::cout << "Before solved: \n";
                        copyBoard.display();
                        std::cout << "Solved: \n";
                        s.display();
                    }
                    else
                    {

                        std::cout << "No solution.\n";
                        
                    }
                    break;
                
                default:
                    break;
                }


            break;
        // case 2:
        //     editing = true;
        //     s.emptyGrid();
            
        //     char editInput;
        //     while(editing)
        //     {
        //         std::cout << "Editing \n";
        //         std::cin >> editInput;
        //         s.display();
        //         switch (editInput)
        //         {
        //         case 'q':
        //         case 'Q':
        //         case 's':
        //         case 'S':
        //             // Saves the current grid as it is
        //             editing = false;
        //             break;
        //         case 'A':
        //         case 'a':
        //             // Moves selection to the left
        //             break;
                
        //         case 'D':
        //         case 'd':
        //             // Moves selection to the right
        //             break;
                    
        //         default:
                    
        //             break;
        //         }
        //     }
        //     continue;
            
            
        case 0:
            running = false;

        default:
            break;
        }
        
    } while(running == true);

    return 0;


}