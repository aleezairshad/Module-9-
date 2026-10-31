#pragma once

class nQueens
{
private:
	int size; // Size of the n-Queens board
	char** board; // 2D dynamic array to represent the n-Queens board
	int numberOfExistingQueens; // Count of queens currently placed on the board
public:
	nQueens(int n); // Constructor to initialize the n-Queens board with size n
	~nQueens();  // Destructor to deallocate the dynamic memory used for the board
	int getSize() const;  // Returns the size of the n-Queens board
	void display() const;  // Displays the current state of the n-Queens board
	int placeQueen(int row, int column);  // function to place a queen on the board at the specified row and column
	bool removeQueen(int row, int column); // function to remove a queen from the board at the specified row and column
	int isConflict(int row, int col) const; // function to check if placing a queen at the specified row and column 
	bool solved() const; // function to check if the n-Queens problem is solved (i.e., all queens are placed without conflicts)

	//using recursion to solve the nQueen problem
	bool solve(int row);
};