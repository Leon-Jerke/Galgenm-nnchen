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
	ReadFile("Dictionary.txt");
}

string Computer::ChooseWord()
{
	int randomIndex = rand() % mDictionary.size();
	return mDictionary[randomIndex];
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
		mDictionary.push_back(word);
	}
}