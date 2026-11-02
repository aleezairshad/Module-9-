#include <iostream>
#include <string>
#include "TowerOfHanoi.h"

using namespace std;

// Precondition: numberOfRings >= 1.
// Postcondition: Stacks all disks on peg A, largest at the bottom.
TowerOfHanoi::TowerOfHanoi(int numberOfRings)
{
    const int ZERO = 0, ONE = 1, PEG_A = 0;
    rings = numberOfRings;
    moves = ZERO;

    for (int disk = rings; disk >= ONE; --disk)
    {
        pegs[PEG_A].push_back(disk);
    }
}

// Precondition: rings >= 1.
// Postcondition: Returns the width of one peg, matching the largest disk.
int TowerOfHanoi::pegWidth() const
{
    const int TWO = 2, ONE = 1;
    return TWO * rings + ONE;
}

// Precondition: pegIndex is 0..2 and level is 0..rings.
// Postcondition: Returns one horizontal slice of a peg (disk or pole).
string TowerOfHanoi::pegSlice(int pegIndex, int level) const
{
    const char POLE = char(186);
    const char BLOCK = char(223);
    const int TWO = 2;

    int width = pegWidth();
    int center = width / TWO;
    string slice(width, ' ');

    if (level < static_cast<int>(pegs[pegIndex].size()))
    {
        int disk = pegs[pegIndex][level];
        string diskArt = string(disk, BLOCK) + to_string(disk) + string(disk, BLOCK);
        int start = (width - static_cast<int>(diskArt.size())) / TWO;
        if (start < 0)
        {
            start = 0;
        }
        for (int i = 0; i < static_cast<int>(diskArt.size()) && start + i < width; ++i)
        {
            slice[start + i] = diskArt[i];
        }
    }
    else
    {
        slice[center] = POLE;
    }

    return slice;
}

// Precondition: rings >= 1.
// Postcondition: Returns the base under one peg.
string TowerOfHanoi::pegBase() const
{
    const char BASE = char(205);
    const char JOINT = char(202);
    const int TWO = 2;

    int width = pegWidth();
    string base(width, BASE);
    base[width / TWO] = JOINT;
    return base;
}

// Precondition: pegIndex is 0..2.
// Postcondition: Returns the letter for that peg.
char TowerOfHanoi::pegLetter(int pegIndex) const
{
    return static_cast<char>('A' + pegIndex);
}

// Precondition: The pegs contain a valid disk arrangement.
// Postcondition: Prints the three pegs, bases, and labels.
void TowerOfHanoi::display() const
{
    const int ZERO = 0, TWO = 2;
    const int INDENT = 8;
    const int GAP = 7;
    const int PEGS = 3;

    string indent(INDENT, ' ');
    string gap(GAP, ' ');
    int width = pegWidth();
    int center = width / TWO;

    cout << "\n";
    for (int level = rings; level >= ZERO; --level)
    {
        cout << indent;
        for (int p = ZERO; p < PEGS; ++p)
        {
            cout << pegSlice(p, level);
            if (p < PEGS - 1)
            {
                cout << gap;
            }
        }
        cout << "\n";
    }

    cout << indent;
    for (int p = ZERO; p < PEGS; ++p)
    {
        cout << pegBase();
        if (p < PEGS - 1)
        {
            cout << gap;
        }
    }
    cout << "\n";

    cout << indent;
    for (int p = ZERO; p < PEGS; ++p)
    {
        string label(width, ' ');
        label[center] = pegLetter(p);
        cout << label;
        if (p < PEGS - 1)
        {
            cout << gap;
        }
    }
    cout << "\n";
}

// Precondition: fromPeg has a disk; the move is legal.
// Postcondition: Moves the top disk, counts the move, and reprints the board.
void TowerOfHanoi::moveDisk(int fromPeg, int toPeg)
{
    int disk = pegs[fromPeg].back();
    pegs[fromPeg].pop_back();
    pegs[toPeg].push_back(disk);
    ++moves;

    cout << "\n        Move #" << moves << ": disk " << disk
        << " from peg-" << pegLetter(fromPeg)
        << " to peg-" << pegLetter(toPeg) << "...\n";
    display();
}

// Precondition: diskCount >= 0; fromPeg, toPeg, and auxPeg are 0..2 and distinct.
// Postcondition: Recursively moves diskCount disks from fromPeg to toPeg using auxPeg.
void TowerOfHanoi::solve(int diskCount, int fromPeg, int toPeg, int auxPeg)
{
    const int ZERO = 0, ONE = 1;
    if (diskCount == ZERO)
    {
        return;
    }

    solve(diskCount - ONE, fromPeg, auxPeg, toPeg);
    moveDisk(fromPeg, toPeg);
    solve(diskCount - ONE, auxPeg, toPeg, fromPeg);
}

// Precondition: All disks start on peg A.
// Postcondition: Moves every disk to peg C using the recursive algorithm.
void TowerOfHanoi::solve()
{
    const int PEG_A = 0, PEG_B = 1, PEG_C = 2;
    solve(rings, PEG_A, PEG_C, PEG_B);
}

// Precondition: None.
// Postcondition: Returns how many disks have been moved.
int TowerOfHanoi::getMoves() const
{
    return moves;
}
