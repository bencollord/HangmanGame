// HangmanGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <time.h>
#include "Utilities.h"
#include "Hangman.h"

using namespace std;
using namespace Utilities;
using namespace HangmanGame;

string words[20] = {
    "efficiency",
    "hat",
    "transportation",
    "complaint",
    "possession",
    "music",
    "apple",
    "football",
    "celebration",
    "relationship",
    "gene",
    "explanation",
    "information",
    "hospital",
    "solution",
    "category",
    "discussion",
    "speech",
    "movie",
    "people"
};

void printTitle();

int main()
{
    srand(time(nullptr));

    string word = words[Math::rand(words->size())];
    auto game = Hangman(word);

    char c;

    do
    {
        game.render(cout);
        cin >> c;
        game.guess(c);
        Console::clear();
    } while (game.isInProgress());

    game.render(cout);
}