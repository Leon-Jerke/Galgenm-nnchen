#include "Person.h"
#include "Logger.h"
#include "Helper.cpp"

#
#include <iostream>
#include <random>

using namespace std;

Person::Person(std::string name)
{
	mName = name;
	mScore = 0;
	mIsGamemaker = false;
}

string Person::ChooseWord()
{
	string guess_word;
	bool correct_word = false;
	do
	{
		cin >> guess_word;
		correct_word = true;
		for (char letter : guess_word)
		{
			if (!isalpha(letter)) {
				cout << endl << "Fehler! Bitte gib nur Buchstaben ein, keine Sonderzeichen oder Zahlen." << endl;
				correct_word = false;
				continue;
			}
		}

	} while (!correct_word);

	return guess_word;
}

string Person::GuessLetterOrWord(vector<char>& guessedLetters)
{
	Logger* logger = Logger::GetInstance();
	string guessed_input;
	bool proceed = true;
	logger->Log("Gib einen Buchstaben oder das volle Wort ein: ");

	do
	{
		guessed_input = "";
		cin >> guessed_input;
		if (guessed_input.length() == 1) // Eingabe von nur einem Buchstaben
		{
			if (!std::isalpha(guessed_input[0]))
			{
				proceed = false;
				logger->Log("Die Eingabe wurde nicht erkannt. Bitte gib einen Buchstaben ein");
			}


			if (Helper::ContainsChar(guessedLetters, guessed_input[0]))
			{
				logger->Log("Der Buchstabe wurde bereits geraten. Versuche einen anderen. ");
				proceed = false;
			}
			else
			{
				guessedLetters.push_back(guessed_input[0]);
				logger->LogOnly("Geratener Buchstabe: " + guessed_input);
			}
		}
		else // Eingabe eines Wortes
		{
			if (std::all_of(begin(guessed_input), end(guessed_input), std::isalpha))
			{

			}
			else
			{
				logger->Log("Das Wort darf keine Sonderzeichen oder Zahlen enthalten. ");
				proceed = false;
			}
		}
	} while (!proceed);

	return guessed_input;
}
