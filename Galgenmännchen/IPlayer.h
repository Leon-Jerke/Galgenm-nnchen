#pragma once
#include <string>
#include <vector>

using namespace std;

// Abstrakte Interface Klasse, um im Spiel nicht zwischen Computer oder Mensch unterscheiden zu müssen
// Beides sind im Grunde einfach nur Spieler. Spiel muss nicht wissen, ob gerade ein Mensch oder der Computer spielt.
// Beide haben die selben Funktionen und unterscheiden sich nur in der Ausführung

class IPlayer			
{
public:
	virtual ~IPlayer() = default;

	virtual string ChooseWord() = 0;		// Methode für den Spielleiter, um ein Wort zu wählen
	virtual string GuessLetterOrWord(vector<char>& guessedLetters) = 0;		// Methode um einen Buchstaben oder ein Wort zu raten. Benötigt eine Liste der bereits geratenen Buchstaben

	string GetName()	// GetName unterscheidet sich bei Person oder Computer nicht in der Ausführung und wird deshalb bereits hier deklariert
	{
		return mName;	// gibt den Namen des Spielers zurück
	}

	void IncreaseScore() // IncreaseScore unterscheidet sich bei Person oder Computer nicht in der Ausführung und wird deshalb bereits hier deklariert
	{
		mScore++;		// erhöht den Score des Spielers um eins
	}

	int GetScore()		// GetScore unterscheidet sich bei Person oder Computer nicht in der Ausführung und wird deshalb bereits hier deklariert
	{
		return mScore;	// gibt den Punktestand des Spielers zurück
	}

protected:				// Member-Variablen, die alle Spieler (Person und Computer) besitzen, werden ebenfalls hier deklariert
	string mName;		
	int mScore;
};