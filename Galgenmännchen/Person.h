#pragma once
#include "IPlayer.h"
#include <string>

using namespace std;

class Person : public IPlayer
{
public:
	Person(std::string Name);
	string ChooseWord() override;
	char GuessLetter() override;
	string GuessWord();
private:
	

};