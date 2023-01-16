#include "Computer.h"
#include "Helper.cpp"
#include <fstream>
#include <algorithm>
#include "Logger.h"

Computer::Computer()			// Konstruktor -> wird bei erstellen eines Objekts der Klasse aufgerufen
{
	mName = "Computer";
	mScore = 0;
	mDictionary = Helper::ReadWordsFromFile("Dictionary.txt");
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
	return "Error";
}

void Computer::AddWordsToDictionary()
{
	Logger* logger = Logger::GetInstance();
	bool add_more_words;
	string new_word;
	do
	{
		bool proceed = false;
		logger->Log("Gib ein neues Wort ein ");
		do
		{
			new_word = "";
			cin >> new_word;
			proceed = true;
			if (!(std::all_of(begin(new_word), end(new_word), std::isalpha))) // Ist jedes Zeichen des eingebenen Wortes ein Buchstabe?
			{
				logger->Log("Das Wort darf keine Sonderzeichen oder Zahlen enthalten. Versuche es erneut: ");
				proceed = false;
			}
			else if (Helper::ContainsString(mDictionary, new_word))
			{
				logger->Log("Das Wort ist bereits im Vokabular enthalten. Versuche es erneut: ");
				proceed = false;
			}
			else
			{
				Helper::AddWordToFile("Dictionary.txt", new_word);
				proceed = true;
			}

		} while (!proceed);

		logger->Log("Willst du ein weiteres Wort eingeben? (y/n) ");
		proceed = false;
		char input;
		do // Frage solange nach einer Eingabe bis eine richtige Antwort gegeben wurde
		{
			std::cin >> input;
			logger->LogOnly("Eingabe: " + input);
			switch (tolower(input))
			{
			case 'y':
				add_more_words = true;
				proceed = true;
				break;
			case 'n':
				add_more_words = false;
				proceed = true;
				break;
			default:
				logger->Log("Die Eingabe wurde nicht erkannt. Bitte gib 'y' pder 'n' ein");
				proceed = false;
				break;
			}
		} while (!proceed);
	} while (add_more_words);
	mDictionary = Helper::ReadWordsFromFile("Dictionary.txt");
}



