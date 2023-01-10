#include <iostream>
#include <random>
#include "Game.h"

int main()
{
    Game game = Game();     // Erstelle Spielinstanz
    game.Setup();           // Einstellungen w�hlen 
    bool continuePlaying = true;    // Hilfsvariable
    do                      // Spiele solange, bis das Spiel beendet wird
    {
        continuePlaying = game.StartRound();
    } while (continuePlaying);

    return 0;
}
