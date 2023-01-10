#include <iostream>
#include <random>
#include "Game.h"

int main()
{
    Game game = Game();     // Erstelle Spielinstanz
    game.Setup();           // Einstellungen wählen 
    bool continuePlaying = true;    // Hilfsvariable
    do                      // Spiele solange, bis das Spiel beendet wird
    {
        continuePlaying = game.StartRound();
    } while (continuePlaying);

    return 0;
}
