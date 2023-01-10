#include "Computer.h"
#include "Helper.cpp"
#include <fstream>
#include <algorithm>

Computer::Computer(int difficulty)			// Konstruktor -> wird bei erstellen eines Objekts der Klasse aufgerufen
{
	mName = "Computer";
	mScore = 0;
	mIsGamemaker = false;
	mDifficulty = difficulty;
	ReadFile("Dictionary.txt");
}

string Computer::ChooseWord()
{
	int randomIndex = rand() % mDictionary.size();  // Zufällige Zahl innerhalb der Größe des Wörterbuchs
	return mDictionary[randomIndex];				// Gebe das Wort an dieser zufälligen Position zurück
}

string Computer::GuessLetterOrWord(vector<char>& guessedLetters)
{
	for (char letter : mLetterGuessOrder)			// For-Schleife welche die Liste der Buchstabenhäufigkeit durchläuft
	{
		string guessedLetter = "";					
		if (!(Helper::ContainsChar(guessedLetters, letter)))	  // Wenn der Buchstabe aus der Liste noch nicht erraten wurde, gib ihn zurück
		{
			guessedLetter.push_back(letter);						// da wir einen String zurück geben müssen, muss der char erst in ein string umgewandelt werden
			return guessedLetter;
		}
	}
}

void Computer::ReadFile(string filePath)
{
	std::ifstream file(filePath);							// Lies Datei ein
	for (std::string word; file >> word; )					// Durchlaufe alle Wörter in der Datei
	{
		mDictionary.push_back(word);					// Füge Wort zum Wörterbuch hinzu
	}
}