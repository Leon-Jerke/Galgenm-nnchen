#pragma once
#include "IPlayer.h"
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

	void Initialize();
	void StartRound();

private:
	void GameTurn();
	void PressAnyKeyToContinue();
	void PrintRules();
	void PrintHangman(int wrongGuesses);
	int	 ChooseGamemode();
	void CreatePlayers();
	void ShufflePlayers();
	void PrintGuessWord();

	std::vector<IPlayer*> mPlayers;
	int				mNumberOfPlayers;
	int				mGamemode;
	string			mGuessWord;
	string			mOutputString;
	vector<char>	mAllGuessedLetters;
	int				mWrongGuesses;
	bool			mSwap;



};