#include "Computer.h"
#include "Helper.cpp"
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
	//int random = rand() % mDictionary.size();
	return "test";
}

string Computer::GuessLetterOrWord(vector<char>& guessedLetters)
{
	for (char letter : mLetterGuessOrder)
	{
		string guessedLetter = "";
		if (!(Helper::ContainsChar(guessedLetters, letter)))
		{
			guessedLetter.push_back(letter);
			return guessedLetter;
		}
	}
}

void Computer::ReadFile(string filePath)
{
	//ifstream word_file;
	std::ifstream file(filePath);
	for (std::string word; file >> word; )
	{
		mDictionary.insert(word);
	}
}