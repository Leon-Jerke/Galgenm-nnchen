#include "Computer.h"
#include <fstream>
#include <algorithm>

Computer::Computer(int difficulty)
{
	mName = "Computer";
	mScore = 0;
	mIsGamemaker = false;
	mDifficulty = difficulty;
	ReadFile("dictionary.txt");
}

string Computer::ChooseWord()
{
	int random = rand() % mDictionary.size();
	return "test";
}

char Computer::GuessLetter()
{
	return 0;
}

void Computer::ReadFile(string filePath)
{
	ifstream file;
	std::ifstream file(filePath);
	for (std::string word; file >> word; )
	{
		mDictionary.insert(word);
	}
}