#pragma once
#include <string>

class IPlayer
{
public:
	virtual ~IPlayer() {};

	virtual string ChooseWord() = 0;
	virtual char GuessLetter() = 0;

	string GetName()
	{
		return mName;
	}

	void SetScore(int score)
	{
		mScore = score;
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