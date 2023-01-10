#include "Person.h"
#include "Logger.h"
#include "Helper.cpp"

#
#include <iostream>
#include <random>

using namespace std;

Person::Person(std::string name)   // Konstruktor -> wird bei erstellen eines Objekts der Klasse Computer aufgerufen
{
	mName = name;
	mScore = 0;
	mIsGamemaker = false;
}

string Person::ChooseWord()
{
	string guess_word;					
	bool correct_word = false;		// Hilfsvariable für die do-while Schleife
	do                              // solange kein korrektes Wort eingeben wurde, versuche es erneut
	{
		cin >> guess_word;			// Input des Spielers
		correct_word = true;		// erstmal davon ausgehen, dass die Eingabe korrekt war
		for (char letter : guess_word)	// Alle Zeichen des eingegebenen Wortes durchlaufen
		{
			if (!isalpha(letter)) {	// Wenn ein Zeichen kein Buchstabe ist, wirf einen Fehler
				cout << endl << "Fehler! Bitte gib nur Buchstaben ein, keine Sonderzeichen oder Zahlen." << endl;
				correct_word = false;
				break;					// Bricht die For-Schleife ab, da bei einem Fehler, der Rest der Schleife nicht mehr durchlaufen werden muss
			}
		}

	} while (!correct_word);

	return guess_word;				// Gibt ein korrektes Wort zurück
}

string Person::GuessLetterOrWord(vector<char>& guessedLetters)
{
	Logger* logger = Logger::GetInstance();			// Holt die Logger Instanz/Objekt um auch hier loggen zu können
	string guessed_input;
	bool proceed;									// Hilfsvariable
	logger->Log("Gib einen Buchstaben oder das volle Wort ein: ");

	do
	{
		guessed_input = "";
		cin >> guessed_input;
		proceed = true;
		if (guessed_input.length() == 1) // Eingabe von nur einem Buchstaben
		{
			if (!std::isalpha(guessed_input[0]))		// Ist das Zeichen kein Buchstabe?
			{
				logger->Log("Die Eingabe wurde nicht erkannt. Bitte gib einen Buchstaben ein");
				proceed = false;						
			}


			if (Helper::ContainsChar(guessedLetters, guessed_input[0]))		// Ist der Buchstabe bereits in der Liste der geratenen Buchstaben?
			{
				logger->Log("Der Buchstabe wurde bereits geraten. Versuche einen anderen. ");
				proceed = false;
			}
		}
		else // Eingabe von mehr als einem Zeichen wird als Wortrate-Versuch gewertet
		{
			if (!(std::all_of(begin(guessed_input), end(guessed_input), std::isalpha))) // Ist jedes Zeichen des eingebenen Wortes ein Buchstabe?
			{
				logger->Log("Das Wort darf keine Sonderzeichen oder Zahlen enthalten. ");
				proceed = false;
			}
		}
	} while (!proceed);

	return guessed_input;
}
