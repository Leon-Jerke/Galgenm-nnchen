#pragma once
#include <vector>

class Player;  // forward declaration


typedef enum
{
	Player_vs_Computer = 1,
	Player_vs_Player = 2
} Gamemode;

class Game
{
public:
	Game();
	~Game() {};

	void Initialize();
	void StartRound();
	void GameTurn();
	void PressAnyKeyToContinue();
	void PrintHangman(int wrongGuesses);

private:
	std::vector<Player*> mPlayers;
	int			mNumberOfPlayers;
	int			mGamemode;
	char*		mGuessWord;
	char*		mOutputString;
	char*		mCorrectLetters;
	char*		mAllGuessedLetters;
	bool		mSwap;



};