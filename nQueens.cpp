#include "nQueens.h"
#include <iostream>
using namespace std;

// precondition: n is a positive integer representing the size of the chessboard
// postcondition: Initializes the nQueens object with a chessboard of size n x n and sets the number of existing queens to 0
nQueens::nQueens(int n)
{
	//create 2D array
	numberOfExistingQueens = 0;
	size = n;
	board = new char* [n];
	for (int i = 0; i < n; i++)
	{
		board[i] = new char[n];
	}

	//fill it with empty signs (based on prof Q's executable it is '-')
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			board[i][j] = '-';
		}
	}
}

// precondition: None
// postcondition: Returns the size of the chessboard (n)
int nQueens::getSize() const
{
	return size;
}

// precondition: None
// postcondition: Displays the current state of the chessboard with Unicode characters for better visualization
void nQueens::display() const
{
	cout << "\n\t" << char(201) << string((size * 2 - 1), char(205)) << char(187);
	for (int i = 0; i < size; i++)
	{
		cout << "\n\t" << char(186);
		for (int j = 0; j < size; j++)
		{
			cout << board[i][j];

			if (j < size - 1)
			{
				cout << char(179);
			}
		}
		cout << char(186);
	}
	cout << "\n\t" << char(200) << string((size * 2 - 1), char(205)) << char(188) << "\n";
}
// precondition: row and col are valid indices for the chessboard
// postcondition: Checks if placing a queen at the specified position (row, col) would result in a conflict with existing queens on the board
int nQueens::isConflict(int row, int col) const
{
	//check directly that position
	if (board[row][col] == 'Q')
	{
		return 1;
	}
	//check row
	for (int i = 0; i < size; i++)
	{
		if (board[row][i] == 'Q')
		{
			return 2;
		}
	}
	//check column
	for (int i = 0; i < size; i++)
	{
		if (board[i][col] == 'Q')
		{
			return 3;
		}
	}
	//check diagonal (4 directions to check)
	//these 2 variables are for increment and decrement (stepping thru the array to check)
	int r = 0;
	int c = 0;
	//upper-left
	r = row - 1;
	c = col - 1;
	while (r >= 0 && c >= 0)
	{
		if (board[r][c] == 'Q')
		{
			return 4;
		}
		r--;
		c--;
	}

	//upper-right
	r = row - 1;
	c = col + 1;

	while (r >= 0 && c < size)
	{
		if (board[r][c] == 'Q')
		{
			return 4;
		}

		r--;
		c++;
	}

	//lower-left
	r = row + 1;
	c = col - 1;

	while (r < size && c >= 0)
	{
		if (board[r][c] == 'Q')
		{
			return 4;
		}

		r++;
		c--;
	}

	//lower-right
	r = row + 1;
	c = col + 1;

	while (r < size && c < size)
	{
		if (board[r][c] == 'Q')
		{
			return 4;
		}

		r++;
		c++;
	}

	return 0;
}

// precondition: row and col are valid indices for the chessboard
// postcondition: Places a queen at the specified position (row, col) if there is no conflict with existing queens on the board; returns 0 if successful, or a conflict type code if there is a conflict
int nQueens::placeQueen(int row, int col)
{
	int conflictType = isConflict(row - 1, col - 1);
	if (conflictType != 0)
	{
		return conflictType;
	}
	else
	{
		numberOfExistingQueens++;
		board[row - 1][col - 1] = 'Q';
		return 0;
	}
}

// precondition: row and col are valid indices for the chessboard
// postcondition: Removes a queen from the specified position (row, col) if there is a queen present; returns true if successful, or false if there was no queen at that position
bool nQueens::removeQueen(int row, int col)
{
	if (board[row - 1][col - 1] == 'Q')
	{
		numberOfExistingQueens--;
		board[row - 1][col - 1] = '-';
		return true;
	}
	else
	{
		return false;
	}
}

// precondition: None
// postcondition: Returns true if the number of existing queens on the board is equal to the size of the chessboard (indicating that the n-Queens problem is solved), or false otherwise
bool nQueens::solved() const
{
	if (numberOfExistingQueens == size)
		return true;
	else
		return false;
}

// precondition: The queen on the first row must have sufficient placement
// postcondition: Return true if the previous rows placement are sufficient and return false if there's no solution to the game
bool nQueens::solve(int row)
{
	if (row > size) //this is the base case. So the function solve 1 row at a time. If the row is bigger than the size means all the rows have sufficient queens.
		return true;

	for (int col = 1; col <= size; col++) //this to loop thru each column of that row and place the queen.
	{
		if (placeQueen(row, col) == 0) //if the queen placed successfully, go to the next row by call the function and + 1 row
		{
			if (solve(row + 1))
				return true;
			//backtrack here to remove queen if there's no sufficient placement on the next row
			removeQueen(row, col);
		}
	}

	//for no solution!
	return false;
}

// precondition: None
// postcondition: De-allocates the memory used for the chessboard by deleting the dynamically allocated 2D array
nQueens::~nQueens()
{
	for (int i = 0; i < size; i++)
	{
		delete[] board[i]; //delete the small array inside big array
	}
	delete[] board; //delete the big board at last
}