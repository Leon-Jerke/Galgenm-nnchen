#include <iostream>
#include "Game.h"

int main()
{
    std::cout << "Hello World!\n";
    Game game = Game();
    game.Initialize();
    game.StartRound();
}
