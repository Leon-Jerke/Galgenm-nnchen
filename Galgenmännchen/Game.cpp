#include "Game.h"
#include "Person.h"
#include "Computer.h"
#include "Logger.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include "Helper.cpp"

using namespace std;

constexpr auto MIN_PLAYER_NUMBER = 2;
constexpr auto MAX_TRYS = 10;

Game::Game() :	mGuessWord(),					// definieren der Spielstartwerte im Konstruktor
				mNumberOfPlayers(0),
				mGamemode(0),
				mWrongGuesses(0),
				mAllGuessedLetters()
{
	mLogger = Logger::GetInstance();			// Pointer einer Logger Instanz holen
}

void Game::Setup()
{	
	mLogger->Log("Willkomen zu Galgenmaennchen!");
	mLogger->Log("Ein Projekt von Leo :D");
	mLogger->Log("");

	PrintRules();					// Ausgeben der Regeln
	PressAnyKeyToContinue();		

	// Wähle den Spielmodus
	do {						// Solange nach Eingabe fragen, bis eine korrekte Eingabe gemacht wurde
		mLogger->Log("Wie moechtest du spielen? (1 = Spieler vs Computer) (2 = Spieler vs Spieler)");
		if (!(std::cin >> mGamemode) || (mGamemode != 1 && mGamemode != 2))
		{
			std::cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << std::endl << "Die Eingabe wurde leider nicht erkannt, bitte versuche es erneut :/" << std::endl;
		}
	} while (mGamemode != 1 && mGamemode != 2);
	mLogger->LogOnly("Gewaehlter Spielmodus: " + to_string(mGamemode));
	mLogger->Log("");

	switch (mGamemode)	// erzeugen der Spieler, abhängig vom Spielmodus
	{
	case Player_vs_Computer:
	{
		Computer* computer_player = new Computer(); // Erstelle Computer Spieler
		mLogger->Log("Moechtest du davor noch weitere Woerter zum Vokabular des Computers hinzufuegen? (y/n)");
		char input;
		bool proceed = false;
		do // Frage solange nach einer Eingabe bis eine richtige Antwort gegeben wurde
		{
			std::cin >> input;
			mLogger->LogOnly("Eingabe: " + input);
			switch (tolower(input))
			{
			case 'y':
				computer_player->AddWordsToDictionary();
				proceed = true;
				break;
			case 'n':
				proceed = true;
				break;
			default:
				mLogger->Log("Die Eingabe wurde nicht erkannt. Bitte gib 'y' pder 'n' ein");
				proceed = false;
				break;
			}
		} while (!proceed);
		mPlayers.push_back(computer_player);			// füge Computer zu Spielern hinzu
		CreatePlayers();									// erstelle Personen Spieler
	}
		break;
	case Player_vs_Player:
	{
		CreatePlayers();		// erstelle nur Personen Spieler
	}
		break;
	default:
		std::cout << "Error: Unbekannter Spielmodus" << std::endl;
		break;
	}
	PressAnyKeyToContinue();
	ShufflePlayers();			// Spieler mischeln und Spielleiter bestimmen
}

bool Game::StartRound()
{ 
	mAllGuessedLetters.clear(); // Zu Beginn die erratenen Buchstaben zurücksetzen
	mWrongGuesses = 0;			// Anzahl an falschen Versuchen zurücksetzen
	mLogger->Log("");
	mLogger->Log(mPlayers[0]->GetName() + ", gebe das zu erratende Wort ein: ");
	mGuessWord = mPlayers[0]->ChooseWord();
	
	vector<string> currentDicitonary = Helper::ReadWordsFromFile("Dictionary.txt");
	if (!(Helper::ContainsString(currentDicitonary, mGuessWord)))
	{
		Helper::AddWordToFile("Dictionary.txt", mGuessWord);
	}

	PressAnyKeyToContinue();
	bool has_won = false;
	while (!has_won && mWrongGuesses < MAX_TRYS)	// Spiele solange, bis ein Spieler gewonnen hat oder die maximale Anzahl an Versuchen erreicht wurde
	{
		for (int i = 1; i < mPlayers.size(); i++)
		{
			if (GameTurn(mPlayers[i]))
			{
				has_won = true;
				break;			// break um auch frühzeitig aus der For-Schleife zu kommen
			}
			mLogger->Log("Naechster Spieler!");
			PressAnyKeyToContinue();
		}
		mLogger->LogOnly("------------------------------------------------");
	}
	mLogger->Log("Moechtet ihr erneut spielen? (y/n)");
	char input;
	do // Frage solange nach einer Eingabe bis eine richtige Antwort gegeben wurde
	{
		std::cin >> input;
		mLogger->LogOnly("Eingabe: " + input);
		switch (tolower(input))
		{
		case 'y':
			return true;
		case 'n':
			return false;
		default:
			mLogger->Log("Die Eingabe wurde nicht erkannt. Bitte gib einen Buchstaben ein");
			break;
		}
	} while (true);
}

bool Game::GameTurn(IPlayer* player)
{
	bool player_turn = true;  // Hilfsvariable
	do						 // Spieler darf solange spielen, bis er eine falsche Eingabe macht oder das Spiel vorbei ist
	{
		// Ausgabe der für die Runde relevanten Informationen
		mLogger->Log(player->GetName() + " ist an der Reihe!");
		PrintGuessWord();
		string guessedLetters = "";
		for (int j = 0; j < mAllGuessedLetters.size(); j++)
		{
			guessedLetters.push_back(mAllGuessedLetters[j]);
			guessedLetters.push_back(',');
		}
		mLogger->Log("");
		mLogger->Log("Geratene Buchstaben: " + guessedLetters);
		PrintHangman(mWrongGuesses);

		// Eingabe der Person oder des Computers
		string guessed_input = player->GuessLetterOrWord(mAllGuessedLetters);			
		mLogger->Log(player->GetName() + " hat '" + guessed_input + "' geraten.");	
		PressAnyKeyToContinue();

		// Überprüfen der Eingabe
		if (guessed_input.length() == 1) // Wenn nur ein Buchstabe geraten wird
		{
			mAllGuessedLetters.push_back(guessed_input[0]); // Geratener Buchstabe in Liste aufnehmen

			if (Helper::ContainsChar(mGuessWord, guessed_input[0]))	// Ist der Buchstabe im Wort enhalten?
			{
				mLogger->Log(string("Korrekt! Der Buchstabe ") + guessed_input[0] + " ist im Wort enthalten"); // Will man mehrere Zeichenfolgen zu einem String zusammenfügen, muss die erste Zeichenfolge explizit zu einem string gecasted werden
				bool all_letters_guessed = PrintGuessWord(); // Gibt das Wort mit den bisher erratenen Buchstaben aus und überprüft ob bereits alle erraten wurden
				
				if (all_letters_guessed) 
				{
					mLogger->Log(string("Glueckwunsch! ") + player->GetName() + " hat gewonnen!");
					player_turn = false;
					player->IncreaseScore();

					std::rotate(mPlayers.begin(), std::find(mPlayers.begin(), mPlayers.end(), player), mPlayers.end()); // Rotiere den Gewinner an erste Stelle des Vectors

					mLogger->Log("Punktestand:");
					for (int i = 0; i < mPlayers.size(); i++)	// Zeige den Score aller Spieler
					{
						mLogger->Log(string(mPlayers[i]->GetName()) + " hat einen Score von " + to_string(mPlayers[i]->GetScore()));
					}

					return true;
				}
				PressAnyKeyToContinue();
			}

			else		// Der Buchstabe ist nicht im Wort enthalten
			{
				mLogger->Log(string("Falsch! Der Buchstabe ") + guessed_input[0] + " ist leider nicht im Wort enthalten");
				player_turn = false;
				mWrongGuesses++;
				PrintHangman(mWrongGuesses);
				PressAnyKeyToContinue();

				if (mWrongGuesses == MAX_TRYS)
				{
					mLogger->Log(string("Das Spiel ist vorbei! Keiner konnte das Wort erraten. Der Spielleiter ") + mPlayers[0]->GetName() + " hat gewonnen.");
					mPlayers[0]->IncreaseScore();

					mLogger->Log("Punktestand:");
					for (int i = 0; i < mPlayers.size(); i++)	// Zeige den Score aller Spieler
					{
						mLogger->Log(string(mPlayers[i]->GetName()) + " hat einen Score von " + to_string(mPlayers[i]->GetScore()));
					}

					return true;
				}
			}
		}
		else // Wenn ein ganzes Wort geraten wird
		{
			if (Helper::EqualStrings(guessed_input, mGuessWord))
			{
				mLogger->Log(string("Korrekt! Du hast das Wort richtig erraten"));
				player_turn = false;
				player->IncreaseScore();

				std::rotate(mPlayers.begin(), std::find(mPlayers.begin(), mPlayers.end(), player), mPlayers.end()); // Rotiere den Gewinner an erste Stelle des Vectors

				mLogger->Log("Punktestand:");
				for (int i = 0; i < mPlayers.size(); i++)	// Zeige den Score aller Spieler
				{
					mLogger->Log(string(mPlayers[i]->GetName()) + " hat einen Score von " + to_string(mPlayers[i]->GetScore()));
				}

				return true;
			}
			else
			{
				mLogger->Log(string("Falsch, das Wort ist nicht richtig!"));
				player_turn = false;
				mWrongGuesses++;
				PressAnyKeyToContinue();

				if (mWrongGuesses == MAX_TRYS)
				{
					PrintHangman(mWrongGuesses);
					mLogger->Log(string("Das Spiel ist vorbei! Keiner konnte das Wort erraten. Der Spielleiter ") + mPlayers[0]->GetName() + " hat gewonnen.");
					mPlayers[0]->IncreaseScore();

					mLogger->Log("Punktestand:");
					for (int i = 0; i < mPlayers.size(); i++)	// Zeige den Score aller Spieler
					{
						mLogger->Log(string(mPlayers[i]->GetName()) + " hat einen Score von " + to_string(mPlayers[i]->GetScore()));
					}

					return true;
				}
			}
		}
	} while (player_turn);

	return false;
}

void Game::CreatePlayers()
{
	mLogger->Log("");
	mLogger->Log("Wie viele Spieler?");

	while (mNumberOfPlayers < MIN_PLAYER_NUMBER)
	{	
		if (!(std::cin >> mNumberOfPlayers))
		{
			std::cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			mLogger->Log("Die Eingabe wurde leider nicht erkannt, bitte versuche es erneut :/");
		}
		else if (mNumberOfPlayers < MIN_PLAYER_NUMBER)
		{
			std::cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << std::endl << "Es werden mindestens 2 Spieler benoetigt" << std::endl;
		}
	}

	mLogger->LogOnly("Anzahl Spieler: " + to_string(mNumberOfPlayers));

	for (size_t i = 1; i <= mNumberOfPlayers; i++)
	{
		mLogger->Log("");
		mLogger->Log(string("Wie heisst Spieler ") + to_string(i) + " ?");
		std::string p_name = "";
		std::cin >> p_name;
		mLogger->LogOnly(string("Spieler ") + to_string(i) + " heisst " + p_name);
		mPlayers.push_back(new Person(p_name));
	}
}

void Game::ShufflePlayers() {
	mLogger->Log("Die Spieler werden gemischelt!");
	mLogger->Log("");
	std::shuffle(mPlayers.begin(), mPlayers.end(), std::mt19937{ std::random_device{}() });
	mLogger->Log(mPlayers[0]->GetName() + " ist der Spielleiter");
	mLogger->Log("");
	mLogger->Log("Die Reihenfolge der Spieler ist: ");

	for (int i = 1; i < mPlayers.size(); i++)
	{
		mLogger->Log(to_string(i) + ": " + mPlayers[i]->GetName());
	}

}

bool Game::PrintGuessWord()
{
	bool gameWon = true;
	string guessWord = "";
	for (int i = 0; i < mGuessWord.length(); i++)
	{
		if (Helper::ContainsChar(mAllGuessedLetters, mGuessWord[i]))
		{
			//cout << mGuessWord[i] << " ";
			guessWord.push_back(mGuessWord[i]);
		}
		else
		{
			//cout << "_ ";
			guessWord.push_back('_');
			gameWon = false;
		}
		guessWord.push_back(' ');
	}
	mLogger->Log(guessWord);
	return gameWon;
}

void Game::PrintRules()
{
	mLogger->Log("");
	mLogger->Log("Die Regeln: ");
	mLogger->Log("Regel 1: ...");
	mLogger->Log("Regel 2: ...");
	mLogger->Log("Regel 3: ...");
	mLogger->Log("Regel 4: ...");
	mLogger->Log("Regel 5: ...");
	mLogger->Log("Regel 6: ...");
}

void Game::PrintHangman(int wrongGuesses)
{
	switch (wrongGuesses)
	{
	case 0:
		mLogger->Log("");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("*                 *");
		mLogger->Log("*                 *");
		mLogger->Log("*                 *");
		mLogger->Log("*                 *");
		mLogger->Log("*                 *");
		mLogger->Log("*                 *");
		mLogger->Log("*                 *");
		mLogger->Log("*                 *");
		mLogger->Log("*                 *");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("");
		break;
	case 1:
		mLogger->Log("");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("*                 *");
		mLogger->Log("*                 *");
		mLogger->Log("*                 *");
		mLogger->Log("*                 *");
		mLogger->Log("*                 *");
		mLogger->Log("*                 *");
		mLogger->Log("*                 *");
		mLogger->Log("*    _____        *");
		mLogger->Log("*   /     \\       *");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("");
		break;
	case 2:
		mLogger->Log("");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("*                 *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |____        *");
		mLogger->Log("*   /     \\       *");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("");
		break;
	case 3:
		mLogger->Log("");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("*     ____        *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |____        *");
		mLogger->Log("*   /     \\       *");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("");
		break;
	case 4:
		mLogger->Log("");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("*     ____        *");
		mLogger->Log("*    |/           *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |____        *");
		mLogger->Log("*   /     \\       *");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("");
		break;
	case 5:
		mLogger->Log("");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("*     ____        *");
		mLogger->Log("*    |/  |        *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |____        *");
		mLogger->Log("*   /     \\       *");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("");
		break;
	case 6:
		mLogger->Log("");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("*     ____        *");
		mLogger->Log("*    |/  |        *");
		mLogger->Log("*    |  (_)       *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |____        *");
		mLogger->Log("*   /     \\       *");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("");
		break;
	case 7:
		mLogger->Log("");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("*     ____        *");
		mLogger->Log("*    |/  |        *");
		mLogger->Log("*    |  (_)       *");
		mLogger->Log("*    |   |        *");
		mLogger->Log("*    |   |        *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |____        *");
		mLogger->Log("*   /     \\       *");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("");
		break;
	case 8:
		mLogger->Log("");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("*     ____        *");
		mLogger->Log("*    |/  |        *");
		mLogger->Log("*    |  (_)       *");
		mLogger->Log("*    |  \\|        *");
		mLogger->Log("*    |   |        *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |____        *");
		mLogger->Log("*   /     \\       *");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("");
		break;
	case 9:
		mLogger->Log("");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("*     ____        *");
		mLogger->Log("*    |/  |        *");
		mLogger->Log("*    |  (_)       *");
		mLogger->Log("*    |  \\|/       *");
		mLogger->Log("*    |   |        *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |____        *");
		mLogger->Log("*   /     \\       *");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("");
		break;
	case 10:
		mLogger->Log("");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("*     ____        *");
		mLogger->Log("*    |/  |        *");
		mLogger->Log("*    |  (_)       *");
		mLogger->Log("*    |  \\|/       *");
		mLogger->Log("*    |   |        *");
		mLogger->Log("*    |  / \\       *");
		mLogger->Log("*    |            *");
		mLogger->Log("*    |____        *");
		mLogger->Log("*   /     \\       *");
		mLogger->Log("* * * * * * * * * *");
		mLogger->Log("");
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