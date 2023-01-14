#pragma once
#include "IPlayer.h"
#include <string>
#include <set>
#include <vector>

using namespace std;

class Computer : public IPlayer
{
public:
	Computer();
	string ChooseWord() override;
	string GuessLetterOrWord(vector<char>& guessedLetters) override;
	void   AddWordsToDictionary();				// F�gt dem W�rterbuch neue W�rter hinzu

private:
	void ReadFile(string filePath);		// Funktion zum Einlesen der W�rterbuch-Datei
	void AddWordToFile(string filePath, string word);

	vector<string> mDictionary;	// W�rterbuch
	// Buchstabenh�ufigkeit in deutschen Texten in absteigender Reihenfolge
	vector<char> mLetterGuessOrder{'E','N','I','S','R','A','T','D','H','U','L','C','G','M','O','B','W','F','K','Z','P','V','�','J','Y','X','Q'};
};