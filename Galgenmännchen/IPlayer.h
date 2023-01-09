#pragma once
#include <string>
#include <vector>

using namespace std;

class IPlayer
{
public:
	virtual ~IPlayer() = default;

	virtual string ChooseWord() = 0;
	virtual string GuessLetterOrWord(vector<char>& guessedLetters) = 0;

	string GetName()
	{
		return mName;
	}

	void IncreaseScore()
	{
		mScore++;
	}

	int GetScore()
	{
		return mScore;
	}
protected:
	string mName;
	int mScore;
	bool mIsGamemaker;
};