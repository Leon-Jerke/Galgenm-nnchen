#pragma once
#include <string>
#include <vector>

using namespace std;

// Abstrakte Interface Klasse, um im Spiel nicht zwischen Computer oder Mensch unterscheiden zu m�ssen
// Beides sind im Grunde einfach nur Spieler. Spiel muss nicht wissen, ob gerade ein Mensch oder der Computer spielt.
// Beide haben die selben Funktionen und unterscheiden sich nur in der Ausf�hrung

class IPlayer			
{
public:
	virtual ~IPlayer() = default;

	virtual string ChooseWord() = 0;		// Methode f�r den Spielleiter, um ein Wort zu w�hlen
	virtual string GuessLetterOrWord(vector<char>& guessedLetters) = 0;		// Methode um einen Buchstaben oder ein Wort zu raten. Ben�tigt eine Liste der bereits geratenen Buchstaben

	string GetName()	// GetName unterscheidet sich bei Person oder Computer nicht in der Ausf�hrung und wird deshalb bereits hier deklariert
	{
		return mName;	// gibt den Namen des Spielers zur�ck
	}

	void IncreaseScore() // IncreaseScore unterscheidet sich bei Person oder Computer nicht in der Ausf�hrung und wird deshalb bereits hier deklariert
	{
		mScore++;		// erh�ht den Score des Spielers um eins
	}

	int GetScore()		// GetScore unterscheidet sich bei Person oder Computer nicht in der Ausf�hrung und wird deshalb bereits hier deklariert
	{
		return mScore;	// gibt den Punktestand des Spielers zur�ck
	}

protected:				// Member-Variablen, die alle Spieler (Person und Computer) besitzen, werden ebenfalls hier deklariert
	string mName;		
	int mScore;
};