#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>
#include "GuessNumber.h"


using namespace std;

// Precondition: max >= 1
// Postcondition: Initializes the maximum number and guess counter.
GuessNumber::GuessNumber(int max)
{
    maximum = max;
    guesses = 0;
}

// Precondition: None
// Postcondition: Starts the recursive number guessing game.
void GuessNumber::play()
{
    guesses = 0;
    cout << "\n\t2> Guess your number between 1 to " << maximum << ".\n";

    cout << "\n\tThink of a number from 1 to " << maximum << ".\n";
    cout << "\n\t";
    system("pause");

    recursiveGuess(1, maximum);

    cout << "\n\tNumber of guesses: " << guesses << "\n";

    cout << "\n\t";
    system("pause");
}

// Precondition: low and high represent the remaining possible numbers.
// Postcondition: Recursively guesses the user's number.
void GuessNumber::recursiveGuess(int low, int high)
{
	const short ONE = 1, TWO = 2;
    // Base case: Only one number remains.
    if (low == high)
    {
        guesses++;

        cout << "\n\tYour number must be " << low << ".\n";

        return;
    }

    // Detect inconsistent answers.
    if (low > high)
    {
        cout << "\n\tYour answers are inconsistent.\n";
        cout << "\tDid you change your number?\n";
        return;
    }

    int middle = low + (high - low) / TWO;

    guesses++;

    char answer;

    // Ask whether the number is correct.
    do
    {
        cout << "\tIs your number " << middle << "? (Y-yes or N-no) ";
        cin >> answer;
        answer = static_cast<char>(toupper(answer));

    } while (answer != 'Y' && answer != 'N');

    // Stopping case: Number found.
    if (answer == 'Y')
    {
        return;
    }

    // Ask whether the number is larger.
    do
    {
        cout << "\tIs your number larger than " << middle << "? (Y-yes or N-no) ";
        cin >> answer;
        answer = static_cast<char>(toupper(answer));

    } while (answer != 'Y' && answer != 'N');

    // Recursive calls
    if (answer == 'Y')
    {
        recursiveGuess(middle + ONE, high);
    }
    else
    {
        recursiveGuess(low, middle - ONE);
    }
}