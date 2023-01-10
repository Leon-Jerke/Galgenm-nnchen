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
	int randomIndex = rand() % mDictionary.size();  // Zuf�llige Zahl innerhalb der Gr��e des W�rterbuchs
	return mDictionary[randomIndex];				// Gebe das Wort an dieser zuf�lligen Position zur�ck
}

string Computer::GuessLetterOrWord(vector<char>& guessedLetters)
{
	for (char letter : mLetterGuessOrder)			// For-Schleife welche die Liste der Buchstabenh�ufigkeit durchl�uft
	{
		string guessedLetter = "";					
		if (!(Helper::ContainsChar(guessedLetters, letter)))	  // Wenn der Buchstabe aus der Liste noch nicht erraten wurde, gib ihn zur�ck
		{
			guessedLetter.push_back(letter);						// da wir einen String zur�ck geben m�ssen, muss der char erst in ein string umgewandelt werden
			return guessedLetter;
		}
	}
}

void Computer::ReadFile(string filePath)
{
	std::ifstream file(filePath);							// Lies Datei ein
	for (std::string word; file >> word; )					// Durchlaufe alle W�rter in der Datei
	{
		mDictionary.push_back(word);					// F�ge Wort zum W�rterbuch hinzu
	}
}