#include <iostream>
#include <random>
#include "Game.h"

int main()
{
    Game game = Game();
    game.Setup();
    bool continuePlaying = true;
    do
    {
        continuePlaying = game.StartRound();
    } while (continuePlaying);

    return 0;
}
