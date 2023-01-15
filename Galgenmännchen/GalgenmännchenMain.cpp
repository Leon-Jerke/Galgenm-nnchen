#include <iostream>
#include <random>
#include "Game.h"
#include <windows.h>

int main()
{
    Game game = Game();     // Erstelle Spielinstanz
    game.Setup();           // Einstellungen wählen 
    bool continuePlaying = true;    // Hilfsvariable
    do                      // Spiele solange, bis das Spiel beendet wird
    {
        continuePlaying = game.StartRound();
        game.PressAnyKeyToContinue();
    } while (continuePlaying);

    //Öffne die GameLog Datei
    LPCWSTR szAction = L"open";
    LPCWSTR szApplicationName = L"notepad.exe";
    LPCWSTR szParameters = L"..\\Galgenmännchen\\GameLog.txt";
    ShellExecute(NULL, szAction, szApplicationName, szParameters, NULL, SW_SHOWDEFAULT);

    return 0;
}
