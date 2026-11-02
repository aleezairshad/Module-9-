#pragma once
#include <vector>
#include <string>

class TowerOfHanoi
{
private:
    int rings;
    int moves;
    std::vector<int> pegs[3];

    int pegWidth() const;
    std::string pegSlice(int pegIndex, int level) const;
    std::string pegBase() const;
    char pegLetter(int pegIndex) const;
    void moveDisk(int fromPeg, int toPeg);
    void solve(int diskCount, int fromPeg, int toPeg, int auxPeg);

public:
    explicit TowerOfHanoi(int numberOfRings);
    void display() const;
    void solve();
    int getMoves() const;
};
