#pragma once

class GuessNumber
{
private:
    int maximum;
    int guesses;

    void recursiveGuess(int low, int high);

public:
    GuessNumber(int max);

    void play();
};