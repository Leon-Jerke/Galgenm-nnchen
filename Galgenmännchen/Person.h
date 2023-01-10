#pragma once
#include "IPlayer.h"
#include <string>

using namespace std;

class Person : public IPlayer
{
public:
	Person(std::string Name);
	string ChooseWord() override;
	string GuessLetterOrWord(vector<char>& guessedLetters) override;

};