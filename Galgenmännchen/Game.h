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
	int	 ChooseGamemode();
	void CreatePlayers();
	bool ContainsChar(vector<char> vec, char c);
	bool ContainsChar(string string, char c);
	void ShufflePlayers();
	bool PrintGuessWord();

	std::vector<IPlayer*> mPlayers;
	int				mNumberOfPlayers;
	int				mGamemode;
	string			mGuessWord;
	string			mOutputString;
	vector<char>	mAllGuessedLetters;
	int				mWrongGuesses;
	bool			mSwap;
	Logger*			mLogger;



};