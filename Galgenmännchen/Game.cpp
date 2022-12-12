#include "Game.h"
#include "Person.h"
#include "Computer.h"
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

	PrintRules();

	mGamemode = ChooseGamemode();

	switch (mGamemode)
	{
	case Player_vs_Computer:
	{
		std::cout << "Wie heisst du?" << std::endl;
		std::string p1_name;
		std::cin >> p1_name;
		mPlayers.push_back(new Person(p1_name));
		mPlayers.push_back(new Computer(1));
	}
		break;
	case Player_vs_Player:
	{

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

int Game::ChooseGamemode()
{
	int gamemode;
	do {
		std::cout << "Wie moechtest du spielen? (1 = Spieler vs Computer) (2 = Spieler vs Spieler)" << std::endl;
		if (!(std::cin >> gamemode) || (gamemode != 1 && gamemode != 2))
		{
			std::cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << std::endl << "Die Eingabe wurde leider nicht erkannt, bitte versuche es erneut :/" << std::endl;
		}
	} while (gamemode != 1 && gamemode != 2);

	return gamemode;
}

void Game::CreatePlayers()
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

void Game::PrintRules()
{
	std::cout << "Die Regeln: " << std::endl;
	std::cout << "Regel 2: ..." << std::endl;
	std::cout << "Regel 1: ..." << std::endl;
	std::cout << "Regel 2: ..." << std::endl;
	std::cout << "Regel 3: ..." << std::endl;
	std::cout << "Regel 4: ..." << std::endl;
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
