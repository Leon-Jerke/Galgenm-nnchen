#pragma once
#include <vector>

class IPlayer;  // forward declaration


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
	void GameTurn();
	void PressAnyKeyToContinue();
	void PrintRules();
	void PrintHangman(int wrongGuesses);
	int	 ChooseGamemode();
	void CreatePlayers();

private:
	std::vector<IPlayer*> mPlayers;
	int			mNumberOfPlayers;
	int			mGamemode;
	char*		mGuessWord;
	char*		mOutputString;
	char*		mCorrectLetters;
	char*		mAllGuessedLetters;
	bool		mSwap;



};