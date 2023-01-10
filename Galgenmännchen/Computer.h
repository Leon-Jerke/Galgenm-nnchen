#pragma once
#include "IPlayer.h"
#include <string>
#include <set>
#include <vector>

using namespace std;

class Computer : public IPlayer
{
public:
	Computer(int difficulty);
	string ChooseWord() override;
	string GuessLetterOrWord(vector<char>& guessedLetters) override;
private:
	void ReadFile(string filePath);

	int mDifficulty;
	vector<string> mDictionary;
	// Buchstabenhäufigkeit in deutschen Texten in absteigender Reihenfolge
	vector<char> mLetterGuessOrder{'E','N','I','S','R','A','T','D','H','U','L','C','G','M','O','B','W','F','K','Z','P','V','ß','J','Y','X','Q'};
};