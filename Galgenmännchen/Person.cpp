#include "Person.h"

Person::Person(std::string name)
{
	mName = name;
	mScore = 0;
	mIsGamemaker = false;
}

string Person::ChooseWord()
{
	return string();
}

char Person::GuessLetter()
{
	return 0;
}

string Person::GuessWord()
{
	return string();
}
