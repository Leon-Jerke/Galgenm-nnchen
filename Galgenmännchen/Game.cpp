#include "Game.h"
#include "Person.h"
#include "Computer.h"
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

constexpr auto MIN_PLAYER_NUMBER = 2;
constexpr auto MAX_TRYS = 10;

Game::Game() :	mGuessWord(),
				mNumberOfPlayers(0),
				mGamemode(0),
				mWrongGuesses(0),
				mSwap(false),
				mOutputString(),
				mAllGuessedLetters()
{
	
}

void Game::Initialize()
{
	std::cout << "Willkomen zu Galgenmaennchen!" << std::endl
	<< "Ein Projekt von Leo :D" << std::endl;

	PrintRules();
	PressAnyKeyToContinue();

	// Wähle den Spielmodus
	do {
		std::cout << "Wie moechtest du spielen? (1 = Spieler vs Computer) (2 = Spieler vs Spieler)" << std::endl;
		if (!(std::cin >> mGamemode) || (mGamemode != 1 && mGamemode != 2))
		{
			std::cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << std::endl << "Die Eingabe wurde leider nicht erkannt, bitte versuche es erneut :/" << std::endl;
		}
	} while (mGamemode != 1 && mGamemode != 2);


	switch (mGamemode)
	{
	case Player_vs_Computer:
	{
		int difficulty;
		do {
			std::cout << std::endl << "Wie stark soll der Computer sein? (1 = schwach, 2 = mittel, 3 = stark)" << std::endl;
			if (!(std::cin >> difficulty) || (difficulty != 1 && difficulty != 2 && difficulty != 3))
			{
				std::cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				std::cout << std::endl << "Die Eingabe wurde leider nicht erkannt, bitte versuche es erneut :/" << std::endl;
			}
		} while (difficulty != 1 && difficulty != 2 && difficulty != 3);
		mPlayers.push_back(new Computer(difficulty));
		CreatePlayers();
	}
		break;
	case Player_vs_Player:
	{
		CreatePlayers();
	}
		break;
	default:
		std::cout << "Error: Unbekannter Spielmodus" << std::endl;
		break;
	}

	StartRound();
}

void Game::StartRound()
{
	ShufflePlayers();

	std::cout << mPlayers[0]->GetName() << ", gebe das zu erratende Wort ein: " << std::endl;
	cin >> mGuessWord;
	PressAnyKeyToContinue();
	bool has_won = false;
	while (!has_won && mWrongGuesses < MAX_TRYS)
	{
		for (int i = 1; i < mPlayers.size(); i++)
		{
			std::cout << std::endl << mPlayers[i]->GetName() << " ist an der Reihe!" << std::endl;

			PrintGuessWord();
			std::cout << std::endl << "Geratene Buchstaben: ";
			for (int j = 0; j < mAllGuessedLetters.size(); j++)
			{
				std::cout << mAllGuessedLetters[j] << ", ";
			}

			PrintHangman(mWrongGuesses);

			char guessed_letter;
			bool proceed = false;
			std::cout << std::endl << "Gib einen Buchstaben ein: ";

			do // Frage solange nach einem Buchstaben, bis ein neuer Buchstabe geraten wird
			{
				do // Frage solange nach einer Eingabe bis ein Buchstabe eingegeben wurde
				{
					std::cin >> guessed_letter;
					if (!std::isalpha(guessed_letter))
					{
						std::cout << std::endl << "Die Eingabe wurde nicht erkannt. Bitte gib einen Buchstaben ein" << std::endl;
					}
				} while (!std::isalpha(guessed_letter));

				if (ContainsChar(mAllGuessedLetters, guessed_letter))
				{
					std::cout << std::endl << "Der Buchstabe wurde bereits geraten. Versuche einen anderen. " << std::endl;
				}
				else 
				{
					mAllGuessedLetters.push_back(guessed_letter);
					proceed = true;
				}
			} while (!proceed);

			if (ContainsChar(mGuessWord, guessed_letter))
			{
				std::cout << "Korrekt! Der Buchstabe " << guessed_letter << " ist im Wort enthalten" << std::endl;
				if (PrintGuessWord())
				{
					std::cout << std::endl << "Glueckwunsch! " << mPlayers[i]->GetName() << " hat gewonnen!" << std::endl;
					mPlayers[i]->IncreaseScore();
					has_won = true;
				}
			}
			else
			{
				std::cout << "Falsch! Der Buchstabe " << guessed_letter << " ist leider nicht im Wort enthalten" << std::endl;
				mWrongGuesses++;
				if (mWrongGuesses == MAX_TRYS)
				{
					std::cout << std::endl << "Das Spiel ist vorbei! Keiner konnte das Wort erraten. Der Spielleiter " << mPlayers[0]->GetName() << " hat gewonnen." << std::endl;
					mPlayers[0]->IncreaseScore();
				}
			}
			PressAnyKeyToContinue();
		}
		std::cout << std::endl << "Moechtet ihr erneut spielen" << std::endl;
	}
}

void Game::GameTurn()
{
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
		mPlayers.push_back(new Person(p_name));
	}
}

void Game::ShufflePlayers() {
	std::shuffle(mPlayers.begin(), mPlayers.end(), std::mt19937{ std::random_device{}() });
	std::cout << std::endl << mPlayers[0]->GetName() << " ist der Spielleiter" << std::endl;
	std::cout << "Die Reihenfolge der Spieler ist: " << std::endl;
	for (int i = 1; i < mPlayers.size(); i++)
	{
		std::cout << i << ": " << mPlayers[i]->GetName() << std::endl;
	}

}

bool Game::PrintGuessWord()
{
	bool gameWon = true;
	for (int i = 0; i < mGuessWord.length(); i++)
	{
		if (ContainsChar(mAllGuessedLetters, mGuessWord[i]))
		{
			std::cout << mGuessWord[i] << " ";
		}
		else
		{
			std::cout << "_ ";
			gameWon = false;
		}
	}
	return gameWon;
}

bool Game::ContainsChar(std::vector<char> vector, char c) 
{
	for (int i = 0; i < vector.size(); i++) {
		if (tolower(vector.at(i)) == tolower(c))
			return true;
	}
	return false;
}

bool Game::ContainsChar(std::string str, char c) {
	for (int i = 0; i < str.length(); i++) {
		if (tolower(str.at(i)) == tolower(c))
			return true;
	}
	return false;
}

void Game::PrintRules()
{
	std::cout << std::endl << "Die Regeln: " << std::endl;
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
		std::cout << std::endl;
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
		std::cout << std::endl;
		break;
	case 1:
		std::cout << std::endl;
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
		std::cout << std::endl;
		break;
	case 2:
		std::cout << std::endl;
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
		std::cout << std::endl;
		break;
	case 3:
		std::cout << std::endl;
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
		std::cout << std::endl;
		break;
	case 4:
		std::cout << std::endl;
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
		std::cout << std::endl;
		break;
	case 5:
		std::cout << std::endl;
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
		std::cout << std::endl;
		break;
	case 6:
		std::cout << std::endl;
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
		std::cout << std::endl;
		break;
	case 7:
		std::cout << std::endl;
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
		std::cout << std::endl;
		break;
	case 8:
		std::cout << std::endl;
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
		std::cout << std::endl;
		break;
	case 9:
		std::cout << std::endl;
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
		std::cout << std::endl;
		break;
	case 10:
		std::cout << std::endl;
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
		std::cout << std::endl;
		break;
	default:
		break;
	}
}

void Game::PressAnyKeyToContinue()
{
	std::cout << std::endl;
	system("pause");
	system("cls");
}