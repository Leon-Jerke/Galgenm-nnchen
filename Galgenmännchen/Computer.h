#pragma once
#include "IPlayer.h"
#include <string>
#include <set>

using namespace std;

class Computer : public IPlayer
{
public:
	Computer(int difficulty);
	string ChooseWord() override;
	char GuessLetter() override;
	void SetDifficulty(int difficulty);
private:
	void ReadFile(string filePath);

	int mDifficulty;
	set<string> mDictionary;
};