//Name: Hany, Aleeza,Thanh, Victor, and Jacob
// Date: 10/30/2026
// Description: Module 9 - Recursive Applications  

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "input.h"
#include "GuessNumber.h"

using namespace std;

// Function Prototypes
char menuOption();
void pattern(int n, int spaces);

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
            //towerOfHanoi();
			break;
        case '4':
            //nQueens();
            break;
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

