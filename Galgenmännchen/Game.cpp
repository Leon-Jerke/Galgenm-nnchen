#include "Game.h"
#include "Player.h"
#include <iostream>

using namespace std;

constexpr auto MIN_PLAYER_NUMBER = 2;

Game::Game() :	mCorrectLetters(nullptr),
				mGuessWord(nullptr),
				mNumberOfPlayers(0),
				mGamemode(0),
				mSwap(false),
				mOutputString(nullptr),
				mAllGuessedLetters(nullptr)
{
	
}

void Game::Initialize()
{
	std::cout << "Willkomen zu Galgenmaennchen!" << std::endl
	<< "Ein Projekt von Leo :D" << std::endl;
	for (size_t i = 0; i <= 10; i++)
	{
		std::cout <<  i << std::endl;
		PrintHangman(i);
	}
	do {
		std::cout << "Wie moechtest du spielen? (1 = Spieler vs Computer) (2 = Player vs Player)" << std::endl;
		if (!(std::cin >> mGamemode) || (mGamemode != 1 && mGamemode != 2))
		{
			std::cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << std::endl << "Die Eingabe wurde leider nicht erkannt, bitte versuche es erneut :/" << std::endl;
		}
	} while (mGamemode != 1 && mGamemode != 2);

	switch (mGamemode)
	{
	case 1:
	{
		std::cout << "Wie heisst du?" << std::endl;
		std::string p1_name;
		std::cin >> p1_name;
		mPlayers.push_back(new Player(p1_name));
		mPlayers.push_back(new Player("Computer"));
	}
		break;
	case 2:
	{
		std::cout << "Wie viele Spieler?" << std::endl;
		while (mNumberOfPlayers < MIN_PLAYER_NUMBER)
		{
			if (!(std::cin >> mNumberOfPlayers))
			{
				std::cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				std::cout << std::endl << "Die Eingabe wurde leider nicht erkannt, bitte versuche es erneut :/" << std::endl;
			}
			else if (mNumberOfPlayers < MIN_PLAYER_NUMBER)
			{
				std::cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				std::cout << std::endl << "Es werden mindestens 2 Spieler benoetigt" << std::endl;
			}
		}
		for (size_t i = 1; i <= mNumberOfPlayers; i++)
		{
			std::cout << "Wie heisst Spieler " << i << " ?" << std::endl;
			std::string p_name;
			std::cin >> p_name;
			mPlayers.push_back(new Player(p_name));
		}
	}
		break;
	default:
		std::cout << "Error: Unbekannter Spielmodus" << std::endl;
		break;
	}

}

void Game::StartRound()
{
	std::cout << "Gebe das zu erratende Wort ein: " << std::endl;

}

void Game::GameTurn()
{
}

void Game::PressAnyKeyToContinue()
{
	system("pause");
	system("cls");
}

void Game::PrintHangman(int wrongGuesses)
{
	switch (wrongGuesses)
	{
	case 0:
		std::cout << "* * * * * * * * * *" << std::endl;
		std::cout << "*                 *" << std::endl;
		std::cout << "*                 *" << std::endl;
		std::cout << "*                 *" << std::endl;
		std::cout << "*                 *" << std::endl;
		std::cout << "*                 *" << std::endl;
		std::cout << "*                 *" << std::endl;
		std::cout << "*                 *" << std::endl;
		std::cout << "*                 *" << std::endl;
		std::cout << "*                 *" << std::endl;
		std::cout << "* * * * * * * * * *" << std::endl;
		break;
	case 1:
		std::cout << "* * * * * * * * * *" << std::endl;
		std::cout << "*                 *" << std::endl;
		std::cout << "*                 *" << std::endl;
		std::cout << "*                 *" << std::endl;
		std::cout << "*                 *" << std::endl;
		std::cout << "*                 *" << std::endl;
		std::cout << "*                 *" << std::endl;
		std::cout << "*                 *" << std::endl;
		std::cout << "*    _____        *" << std::endl;
		std::cout << "*   /     \\       *" << std::endl;
		std::cout << "* * * * * * * * * *" << std::endl;
		break;
	case 2:
		std::cout << "* * * * * * * * * *" << std::endl;
		std::cout << "*                 *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |____        *" << std::endl;
		std::cout << "*   /     \\       *" << std::endl;
		std::cout << "* * * * * * * * * *" << std::endl;
		break;
	case 3:
		std::cout << "* * * * * * * * * *" << std::endl;
		std::cout << "*     ____        *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |____        *" << std::endl;
		std::cout << "*   /     \\       *" << std::endl;
		std::cout << "* * * * * * * * * *" << std::endl;
		break;
	case 4:
		std::cout << "* * * * * * * * * *" << std::endl;
		std::cout << "*     ____        *" << std::endl;
		std::cout << "*    |/           *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |____        *" << std::endl;
		std::cout << "*   /     \\       *" << std::endl;
		std::cout << "* * * * * * * * * *" << std::endl;
		break;
	case 5:
		std::cout << "* * * * * * * * * *" << std::endl;
		std::cout << "*     ____        *" << std::endl;
		std::cout << "*    |/  |        *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |____        *" << std::endl;
		std::cout << "*   /     \\       *" << std::endl;
		std::cout << "* * * * * * * * * *" << std::endl;
		break;
	case 6:
		std::cout << "* * * * * * * * * *" << std::endl;
		std::cout << "*     ____        *" << std::endl;
		std::cout << "*    |/  |        *" << std::endl;
		std::cout << "*    |  (_)       *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |____        *" << std::endl;
		std::cout << "*   /     \\       *" << std::endl;
		std::cout << "* * * * * * * * * *" << std::endl;
		break;
	case 7:
		std::cout << "* * * * * * * * * *" << std::endl;
		std::cout << "*     ____        *" << std::endl;
		std::cout << "*    |/  |        *" << std::endl;
		std::cout << "*    |  (_)       *" << std::endl;
		std::cout << "*    |   |        *" << std::endl;
		std::cout << "*    |   |        *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |____        *" << std::endl;
		std::cout << "*   /     \\       *" << std::endl;
		std::cout << "* * * * * * * * * *" << std::endl;
		break;
	case 8:
		std::cout << "* * * * * * * * * *" << std::endl;
		std::cout << "*     ____        *" << std::endl;
		std::cout << "*    |/  |        *" << std::endl;
		std::cout << "*    |  (_)       *" << std::endl;
		std::cout << "*    |  \\|        *" << std::endl;
		std::cout << "*    |   |        *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |____        *" << std::endl;
		std::cout << "*   /     \\       *" << std::endl;
		std::cout << "* * * * * * * * * *" << std::endl;
		break;
	case 9:
		std::cout << "* * * * * * * * * *" << std::endl;
		std::cout << "*     ____        *" << std::endl;
		std::cout << "*    |/  |        *" << std::endl;
		std::cout << "*    |  (_)       *" << std::endl;
		std::cout << "*    |  \\|/       *" << std::endl;
		std::cout << "*    |   |        *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |____        *" << std::endl;
		std::cout << "*   /     \\       *" << std::endl;
		std::cout << "* * * * * * * * * *" << std::endl;
		break;
	case 10:
		std::cout << "* * * * * * * * * *" << std::endl;
		std::cout << "*     ____        *" << std::endl;
		std::cout << "*    |/  |        *" << std::endl;
		std::cout << "*    |  (_)       *" << std::endl;
		std::cout << "*    |  \\|/       *" << std::endl;
		std::cout << "*    |   |        *" << std::endl;
		std::cout << "*    |  / \\       *" << std::endl;
		std::cout << "*    |            *" << std::endl;
		std::cout << "*    |____        *" << std::endl;
		std::cout << "*   /     \\       *" << std::endl;
		std::cout << "* * * * * * * * * *" << std::endl;
		break;
	default:
		break;
	}
}
