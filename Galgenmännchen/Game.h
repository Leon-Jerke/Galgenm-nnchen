#pragma once
#include "IPlayer.h"
#include "Logger.h"
#include <vector>

enum Gamemodes		// enum helfen die Lesbarkeit des Codes zu verbessern. Statt 1 und 2 kann im Code der tatsächliche Wortlaut verwendet werden
{
	Player_vs_Computer = 1,
	Player_vs_Player = 2
};

class Game
{
public:
	Game();			// Konstruktor
	~Game() {};		// Destruktor

	void Setup();		// Setup Methode die einmalig zu Beginn aufgerufen wird um die Einstellungen zu treffen
	bool StartRound();	// Startet eine neue Runde Galgenmännchen
	void PressAnyKeyToContinue();		// Bereinigt die Konsole

private:
	void PrintRules();					// Gibt die Spielregeln aus
	void PrintHangman(int wrongGuesses);	// Gibt den aktuellen Zustand des Galgenmännchens aus
	void CreatePlayers();					// erzeugt die Personen Spieler
	void ShufflePlayers();					// Mischelt die Spieler
	bool PrintGuessWord();					// gibt das Ratewort nur mit Unterstrichen und den erratenen Buchstaben aus
	bool GameTurn(IPlayer* player);			// Spielzug eines Spielers

	std::vector<IPlayer*> mPlayers;			// Liste der Spieler
	int				mNumberOfPlayers;		// Anzahl der Spieler
	int				mGamemode;				// Spielmodus 
	string			mGuessWord;				// Wort das erraten werden muss
	vector<char>	mAllGuessedLetters;		// Liste der bisher geratenen Buchstaben
	int				mWrongGuesses;			// Anzahl der misslungenen Versuche
	Logger*			mLogger;				// Pointer auf eine Logger Instanz um das Spiel zu dokument
};