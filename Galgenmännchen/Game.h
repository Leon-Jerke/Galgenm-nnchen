#pragma once
#include "IPlayer.h"
#include "Logger.h"
#include <vector>

enum Gamemodes
{
	Player_vs_Computer = 1,
	Player_vs_Player = 2
};

class Game
{
public:
	Game();
	~Game() {};

	void Setup();
	bool StartRound();

private:
	void PressAnyKeyToContinue();
	void PrintRules();
	void PrintHangman(int wrongGuesses);
	void CreatePlayers();
	bool ContainsChar(const vector<char>& vec, const char& c);
	bool ContainsChar(const string& string, const char& c);
	bool EqualStrings(const string& string1, const string& string2);
	void ShufflePlayers();
	bool PrintGuessWord();
	bool GameTurn(IPlayer* player);

	std::vector<IPlayer*> mPlayers;
	int				mNumberOfPlayers;
	int				mGamemode;
	string			mGuessWord;
	vector<char>	mAllGuessedLetters;
	int				mWrongGuesses;
	Logger*			mLogger;
};