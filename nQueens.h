#pragma once

class nQueens
{
private:
	int size; // Size of the n-Queens board
	char** board; // 2D dynamic array to represent the n-Queens board
	int numberOfExistingQueens; // Count of queens currently placed on the board

	// Hany Add these
	bool* usedColumns; // Array to keep track of used columns for efficient conflict checking
    bool* usedDiagonal1; // Array to keep track of used diagonals (top-left to bottom-right)
    bool* usedDiagonal2; // Array to keep track of used diagonals (top-right to bottom-left)

	int* queenColumns; // Array to store the column positions of queens for each row
	int* columnCounts; // Array to count the number of queens in each column
	int* diagonal1Counts; // Array to count the number of queens in each diagonal (top-left to bottom-right)
	int* diagonal2Counts; // Array to count the number of queens in each diagonal (top-right to bottom-left)

	int countConflicts(int row, int col) const; // Function to count the number of queens attacking a specific position (row, col)
	bool solveLargeBoard(int step, int maxSteps); // Function to recursively improve the arrangement of queens on the board

public:
	explicit nQueens(int n); // Constructor to initialize the n-Queens board with size n
	~nQueens(); // Destructor to deallocate the dynamic memory used for the board

	int getSize() const; // Returns the size of the n-Queens board
	void display() const; // Displays the current state of the n-Queens board
	int placeQueen(int row, int column); // function to place a queen on the board at the specified row and column
	bool removeQueen(int row, int column); // function to remove a queen from the board at the specified row and column
	int isConflict(int row, int col) const; // function to check if placing a queen at the specified row and column would result in a conflict with existing queens on the board
	bool solved() const; // function to check if the n-Queens problem is solved (i.e., all queens are placed without conflicts)
	// using recursion to solve the nQueen problem
    bool solve(int row); 
	// Hany Add these to prevent copying of nQueens objects
	nQueens(const nQueens&) = delete; // Delete copy constructor to prevent copying of nQueens objects
	nQueens& operator=(const nQueens&) = delete; // Delete copy assignment operator to prevent copying of nQueens objects
};
