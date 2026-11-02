#include "nQueens.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

// Precondition: n >= 1.
// Postcondition: Creates an empty n-by-n chessboard and tracking arrays.
nQueens::nQueens(int n)
{
	const int ONE = 1, TWO = 2;
    //create 2D array
    numberOfExistingQueens = 0;
    size = n;
    board = new char* [size];
    for (int r = 0; r < size; ++r)
    {
		board[r] = new char[size]; // Allocate memory for each row
		for (int c = 0; c < size; ++c) // Initialize each cell to '-'
        {
            board[r][c] = '-';
        }
    }

	// ---Hany Add these to initialize the tracking arrays ---
	usedColumns = new bool[size](); // Initialize all elements to false
	usedDiagonal1 = new bool[TWO * size - ONE](); // Initialize all elements to false
	usedDiagonal2 = new bool[TWO * size - ONE](); // Initialize all elements to false

	queenColumns = new int[size]; // Initialize all elements to -1
	columnCounts = new int[size](); // Initialize all elements to 0
	diagonal1Counts = new int[TWO * size - ONE](); // Initialize all elements to 0
	diagonal2Counts = new int[TWO * size - ONE](); // Initialize all elements to 0
	// Initialize queenColumns to -1 to indicate no queens are placed in any row
    for (int r = 0; r < size; ++r)
    {
		queenColumns[r] = -1; // Initialize all elements to -1
    }
}


// Precondition: None.
// Postcondition: Returns the board dimension.
int nQueens::getSize() const
{
    return size;
}

// Precondition: None.
// Postcondition: Prints the current chessboard.
void nQueens::display() const
{
	const int ONE = 1, TWO = 2;
    cout << "\n\t" << char(201) << string(size * TWO - ONE, char(205)) << char(187);
    for (int r = 0; r < size; ++r)
    {
        cout << "\n\t" << char(186);
        for (int c = 0; c < size; ++c)
        {
            cout << board[r][c];
            if (c < size - ONE)
                cout << char(179);
        }
        cout << char(186);
    }
    cout << "\n\t" << char(200) << string(size * TWO - ONE, char(205)) << char(188) << "\n";
}

// ---Hany modified the isConflict function to use the tracking arrays for efficient conflict checking ---
//Precondition: row and col are valid zero-based board indices.
//Postcondition: Returns 0 if the position is safe, otherwise returns a conflict code.
int nQueens::isConflict(int row, int col) const
{
	const int ONE = 1;
    if (board[row][col] == 'Q')
    {
        return 1;
    }
    for (int c = 0; c < size; ++c)
    {
        if (board[row][c] == 'Q')
        {
            return 2;
        }
    }
    if (usedColumns[col])
    {
        return 3;
    }
    if (usedDiagonal1[row - col + size - ONE] || usedDiagonal2[row + col])
    {
        return 4;
    }
    return 0;
}


// Precondition: row and col are one-based indices within the board.
// Postcondition: Places a queen if safe and returns 0, otherwise returns a conflict code.
int nQueens::placeQueen(int row, int col)
{
	const int ONE = 1;
	int r = row - ONE; // Convert to zero-based index
	int c = col - ONE; // Convert to zero-based index   
	int conflict = isConflict(r, c); // Check for conflicts before placing the queen
    if (conflict != 0)
    {
        return conflict;
    }

	// ---Hany Add these to update the tracking arrays when placing a queen---
	board[r][c] = 'Q'; // Place the queen on the board
	++numberOfExistingQueens; // Increment the count of existing queens
	usedColumns[c] = true; // Mark the column as used
	usedDiagonal1[r - c + size - 1] = true; // Mark the diagonal (top-left to bottom-right) as used
	usedDiagonal2[r + c] = true; // Mark the diagonal (top-right to bottom-left) as used
	queenColumns[r] = c; // Store the column position of the queen for this row
    return 0;
}

// Precondition: row and col are one-based indices within the board.
// Postcondition: Removes an existing queen and updates the tracking arrays.
bool nQueens::removeQueen(int row, int col)
{
    int r = row - 1;
    int c = col - 1;
    if (board[r][c] != 'Q')
    {
        return false;
    }

	// ---Hany Add these to update the tracking arrays when removing a queen---
	board[r][c] = '-'; // Remove the queen from the board
	--numberOfExistingQueens; // Decrement the count of existing queens
	usedColumns[c] = false; // Mark the column as unused
	usedDiagonal1[r - c + size - 1] = false; // Mark the diagonal (top-left to bottom-right) as unused
	usedDiagonal2[r + c] = false; // Mark the diagonal (top-right to bottom-left) as unused
	queenColumns[r] = -1; // Reset the column position of the queen for this row

    return true;
}

// Precondition: None.
// Postcondition: Returns true if the board contains n safely placed queens.
bool nQueens::solved() const
{
    return numberOfExistingQueens == size;
}

// ---Hany Add these to implement the min-conflicts algorithm for larger boards ---
// Precondition: row and col are valid zero-based indices.
// Postcondition: Returns the number of queens attacking this position in the temporary arrangement.
int nQueens::countConflicts(int row, int col) const
{
	const int ONE = 1;
	// Count the number of queens attacking the position (row, col) in the temporary arrangement.
    int conflicts = columnCounts[col] + diagonal1Counts[row - col + size - ONE] + diagonal2Counts[row + col];

    // The queen already at (row, col) is counted three times.
    if (queenColumns[row] == col)
    {
        conflicts -= 3;
    }
    return conflicts;
}

// ---Hany Add these to implement the min-conflicts algorithm for larger boards ---
// Precondition: The first queen is placed on row 1; row is initially 2.
// Postcondition: Recursively improves the arrangement of queens on the board.
bool nQueens::solveLargeBoard(int step, int maxSteps)
{
	const int ONE = 1;
    // Select a random conflicted queen, excluding the fixed first row.
    int selectedRow = -1;
    int conflictingRows = 0;
    for (int r = 1; r < size; ++r)
    {
        if (countConflicts(r, queenColumns[r]) > 0)
        {
            ++conflictingRows;
            if (rand() % conflictingRows == 0)
            {
                selectedRow = r;
            }
        }
    }

    // Check the fixed queen too: it can be attacked by other rows.
    if (selectedRow == -1)
    {
        return countConflicts(0, queenColumns[0]) == 0;
    }

    if (step >= maxSteps)
    {
        return false;
    }

    // Choose a column with the fewest conflicts; break ties randomly.
    int bestCol = -1;
    int bestScore = size + ONE;
    int ties = 0;
    for (int c = 0; c < size; ++c)
    {
        int score = countConflicts(selectedRow, c);
        if (score < bestScore)
        {
            bestScore = score;
            bestCol = c;
            ties = 1;
        }
        else if (score == bestScore)
        {
            ++ties;
            if (rand() % ties == 0)
            {
                bestCol = c;
            }
        }
    }

    // Move the selected queen in the temporary arrangement.
	int oldCol = queenColumns[selectedRow]; // Store the old column before moving
	--columnCounts[oldCol];   // Decrement the count for the old column
	--diagonal1Counts[selectedRow - oldCol + size - ONE]; // Decrement the count for the old diagonal (top-left to bottom-right)
	--diagonal2Counts[selectedRow + oldCol]; // Decrement the count for the old diagonal (top-right to bottom-left)

	queenColumns[selectedRow] = bestCol; // Move the queen to the new column
	++columnCounts[bestCol];  // Increment the count for the new column
	++diagonal1Counts[selectedRow - bestCol + size - ONE]; // Increment the count for the new diagonal (top-left to bottom-right)
	++diagonal2Counts[selectedRow + bestCol]; // Increment the count for the new diagonal (top-right to bottom-left)

	return solveLargeBoard(step + ONE, maxSteps); // Recursive call to continue improving the arrangement
}

// ---Hany modified the solve function to use a hybrid approach for larger boards ---
// Precondition: The first queen is placed on row 1; row is initially 2.
// Postcondition: Finds a valid arrangement if successful, preserving row 1.
bool nQueens::solve(int row)
{
	const int ONE = 1;
    if (row > size)
    {
        return true;
    }

    // Exact recursive backtracking for smaller boards.
    if (size < 12 || row != 2)
    {
        for (int col = 1; col <= size; ++col)
        {
            if (placeQueen(row, col) == 0)
            {
                if (solve(row + ONE))
                {
                    return true;
                }
                removeQueen(row, col);
            }
        }
        return false;
    }

    // Larger boards: bounded recursive min-conflicts with random restarts.
    const int maxRestarts = 300;
    const int maxSteps = 20 * size;
    const int fixedColumn = queenColumns[0];
    if (fixedColumn < 0)
    {
        return false;
    }

    for (int attempt = 0; attempt < maxRestarts; ++attempt)
    {
        for (int i = 0; i < size; ++i)
        {
            columnCounts[i] = 0;
        }
        for (int i = 0; i < 2 * size - ONE; ++i)
        {
            diagonal1Counts[i] = 0;
            diagonal2Counts[i] = 0;
        }

        // Build a temporary arrangement. The first queen never moves.
        for (int r = 0; r < size; ++r)
        {
            int c = (r == 0) ? fixedColumn : rand() % size;
            queenColumns[r] = c;
            ++columnCounts[c];
            ++diagonal1Counts[r - c + size - ONE];
            ++diagonal2Counts[r + c];
        }

        if (solveLargeBoard(0, maxSteps))
        {
            // The temporary solution is safe. Copy it onto the real board.
            for (int r = 1; r < size; ++r)
            {
                int c = queenColumns[r];
                if (placeQueen(r + ONE, c + ONE) != 0)
                {
                    return false; // Defensive check; should never happen.
                }
            }
            return solved();
        }
    }

    // Search limit reached; no solution found within the attempt budget.
    return false;
}

// Precondition: None.
// Postcondition: Releases all dynamically allocated memory.
nQueens::~nQueens()
{
    for (int r = 0; r < size; ++r)
    {
        delete[] board[r];
    }
    delete[] board;
    delete[] usedColumns;
    delete[] usedDiagonal1;
    delete[] usedDiagonal2;
    delete[] queenColumns;
    delete[] columnCounts;
    delete[] diagonal1Counts;
    delete[] diagonal2Counts;
}
