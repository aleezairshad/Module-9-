//Name: Hany, Aleeza,Thanh, Victor, and Jacob
// Date: 10/30/2026
// Description: Module 9 - Recursive Applications  

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "input.h"
#include "GuessNumber.h"
#include "nQueens.h"
#include "TowerOfHanoi.h"


using namespace std;

// Function Prototypes
char menuOption();
void pattern(int n, int spaces);
void runNQueens();
void runTowerOfHanoi();


int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    bool running = true;
    char option;
    while (running)
    {
        system("cls");
        option = menuOption();
        switch (option)
        {
        case '1':
        {
            system("cls");
            const int THREE = 3, ZERO = 0;
            cout << "\n\t1> Pattern of astricks and blanks\n\n";

            pattern(THREE, ZERO);

            cout << "\n\n";
            system("pause");
            break;
        }
        case '2':
        {
            system("cls");
            int maximum = rand() % 1000 + 1;

            GuessNumber game(maximum);

            game.play();

            break;
        }
        case '3':
        {
            system("cls");
            runTowerOfHanoi();
            break;
        }
        case '4':
        {
            system("cls");

            runNQueens();

            cout << "\n";
            system("pause");

            break;

        }
        case '0':
            running = false;
            break;
        default:
            cout << "\n\t\t  Invalid option. Please try again.\n";
            break;
        }
    }

    return 0;
}

char menuOption()
{
    cout << "\t\t  CMPR131 Chapter 9: Recursive Applications by Hany, Aleeza, Thanh, Victor, and Jacob (10/30/2026)\n";
    cout << "\t\t" << string(100, char(205));
    cout << "\n\t\t  1> Pattern of astricks and blanks";
    cout << "\n\t\t  2> Guess a number";
    cout << "\n\t\t  3> Solve Tower of Hanoi";
    cout << "\n\t\t  4> Solve n-Queens\n";
    cout << "\t\t" << string(100, char(196));
    cout << "\n\t\t  0 > Exit\n";
    cout << "\t\t" << string(100, char(205));

    char option = toupper(inputChar("\n\t\t  option: ", static_cast<string>("1,2,3,4,0")));
    return option;
}

// Precondition: n >= 0 and spaces >= 0
// Postcondition: Displays the recursive pattern of asterisks and blanks.
void pattern(int n, int spaces)
{
    const int ONE = 1;
    // Base case
    if (n == 0)
    {
        cout << "\t" << string(spaces, ' ') << "*\n";
        return;
    }

    // First recursive call
    pattern(n - ONE, spaces);

    // Print a horizontal row of asterisks
    cout << "\t" << string(spaces, ' ');

    for (int i = 0; i < (1 << n); i++)
    {
        cout << "* ";
    }

    cout << "\n";

    // Second recursive call
    pattern(n - ONE, spaces + (1 << n));
}

// Precondition: None.
// Postcondition: Runs Tower of Hanoi until the user chooses not to play again.
void runTowerOfHanoi()
{
    const int ONE = 1, MAX_RINGS = 64, TITLE_LINE = 97;
    char again = 'Y';

    while (again == 'Y')
    {
        system("cls");
        cout << "Tower of Hanoi (Recursive)\n";
        cout << string(TITLE_LINE, char(196)) << "\n";

        int rings = inputInteger("\n        Enter the number of rings (1..64): ", ONE, MAX_RINGS);
        TowerOfHanoi game(rings);

        game.display();
        game.solve();

        cout << "\n        The computer has solved the game in " << game.getMoves() << " moves.\n";
        again = inputChar("\n        Play again? (Y-yes or N-no) ", 'Y', 'N');
    }
}

// --Hany modified the runNQueens function to use the updated nQueens class with tracking arrays for efficient conflict checking.
// Precondition: None.
// Postcondition: Runs the n-Queens problem solver and displays the solution if found.
void runNQueens()
{
    const int ONE = 1, ZERO = 0, TWO = 2;

    int size = inputInteger("\n\n\tEnter the board dimension nxn: ", 1, 100); // Input the board size from the user
    // Check for invalid board sizes (2 and 3) and prompt the user to enter a valid size
    while (size == 2 || size == 3)
    {
        cout << "\n\tERROR: size cannot be " << size << ", because there is no solution.";
        size = inputInteger("\n\tEnter the board dimension nxn: ", 1, 100); // Prompt the user to enter a valid board size
    }
    nQueens board(size); // Create an instance of the nQueens class with the specified board size

    //let the user choose the column to place the queen on the 1st row
    cout << "\n\tEnter the column position(1.." << size << ") of the first Queen on row 1: ";
    int firstColumn = inputInteger("", ONE, size);
    board.placeQueen(ONE, firstColumn);
    //Recursive takes place here
    bool foundSolution = board.solve(TWO);

    if (foundSolution)
    {
        board.display();
    }
    else
    {
        cout << "\n\tNo solution!";
    }

}
