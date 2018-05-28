#include "Source.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <time.h>
#include <Windows.h>

using namespace std;

struct Player
{
	string name;
	int entryNumber;
	string currentPasscode;
	UINT misguessedLetterCount;
	vector<char> passcodeHistory;
	time_t playTime;

	Player() :
		name(""),
		entryNumber(0),
		currentPasscode(""),
		misguessedLetterCount(0),
		passcodeHistory(),
		playTime(0)
	{
	}
};

const int passcodeCount = 100;
const int sceneCount = 10;
const int playerCount = 5;

void LoadPasscodes(string* passcodes)
{
	ifstream file = ifstream("passcodes.txt");
	if (file.is_open())
	{
		for (int i = 0; i < passcodeCount; ++i)
		{
			file >> passcodes[i];
		}
	}
}

void LoadScenes(string* scenes)
{
	ifstream file = ifstream("scenes.txt");
	if (file.is_open())
	{
		int index = 0;
		for (int i = 0; i < sceneCount; ++i)
		{
			while (true)
			{
				string line;
				getline(file, line);
				if (line.empty())
					break;
				scenes[i] += line + "\n";
			}
		}
	}
}

void LoadPlayers(Player* players)
{
	for (int i = 0; i < playerCount; ++i)
	{
		cout << "Enter player" << (i + 1) << " name: ";
		cin >> players[i].name;
		cout << "Enter player" << (i + 1) << " entry number: ";
		cin >> players[i].entryNumber;
		//players[i].name = "Player";
		//players[i].name += ('1' + i);
	}
	cout << endl;
}

size_t FindIndex(const vector<char>& vec, char c)
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		if (vec[i] == c)
			return i;
	}
	return -1;
}

void PrintGuessedCharacters(const Player& player)
{
	cout << "Guessed letters: ";
	for (char i = 'A'; i <= 'Z'; ++i)
	{
		size_t index = FindIndex(player.passcodeHistory, i);
		if (index != -1)
		{
			cout << '*';
		}
		else
		{
			cout << i;
		}
	}
}

void PrintColor(ostream& outputStream, WORD color, TCHAR* str)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(hConsole, &buf);
	WORD oldColor = buf.wAttributes;
	SetConsoleTextAttribute(hConsole, color);
	outputStream << str;
	SetConsoleTextAttribute(hConsole, oldColor);
}

bool GuessCharacter(Player& player, char guess, char* passcodeDisplay, const char* passcode, int passcodeLength)
{
	bool ret = false;
	if (guess >= 'a' && guess <= 'z')
		guess += 'A' - 'a';
	if (guess < 'A' || guess > 'Z')
	{
		cout << "Words contain only letters" << endl;
		Sleep(1000);
		return true;
	}
	if (FindIndex(player.passcodeHistory, guess) != -1)
	{
		cout << "You already guessed this letter" << endl;
		Sleep(1000);
		return true;
	}
	player.passcodeHistory.push_back(guess);
	char* passcodeEnd = (char*)passcode + passcodeLength;
	while (passcode < passcodeEnd)
	{
		char upper = *passcode;
		if (upper >= 'a' && upper <= 'z')
			upper += 'A' - 'a';
		if (upper == guess)
		{
			*passcodeDisplay = *passcode;
			ret = true;
		}

		passcode++;
		passcodeDisplay++;
	}
	return ret;
}

void GameLoop(string* passcodes, string* scenes, Player* players)
{
	UINT bestPlayerIndex = 0;
	for (UINT playerIndex = 0; playerIndex < playerCount; ++playerIndex)
	{
		// for every player
		int passcodeIndex = (int)(rand() / (float)RAND_MAX * passcodeCount);
		int passcodeLength = passcodes[passcodeIndex].length();
		char* passcode = new char[passcodeLength + 1];
		memcpy(passcode, passcodes[passcodeIndex].c_str(), sizeof(char) * passcodeLength);
		players[playerIndex].currentPasscode = passcodes[passcodeIndex];
		passcode[passcodeLength] = '\0';
		char* passcodeDisplay = new char[passcodeLength + 1];
		for (int i = 0; i < passcodeLength; ++i)
		{
			passcodeDisplay[i] = '*';
		}
		passcodeDisplay[passcodeLength] = '\0';

		time_t timeStart = time(0);

		int sceneIndex = 0;
		while (true)
		{
			// draw scene
			// draw guessing word with guessed characters displayed
			// let current player guess

			system("cls");

			cout << scenes[sceneIndex] << endl;
			cout << passcodeDisplay << endl << endl;

			if (sceneIndex >= sceneCount - 3)
			{
				PrintColor(cout, 12, "WARNING");
				cout << " you have only ";
			}
			cout << sceneCount - sceneIndex << " guesses left" << endl << endl;

			PrintGuessedCharacters(players[playerIndex]);

			cout << endl;
			cout << passcode << endl;
			cout << players[playerIndex].name << "'s guess: ";
			char c;
			cin >> c;

			if (!GuessCharacter(players[playerIndex], c, passcodeDisplay, passcode, passcodeLength))
			{
				sceneIndex++;
				players[playerIndex].misguessedLetterCount++;
				if (sceneIndex >= sceneCount)
				{
					cout << players[playerIndex].name;
					PrintColor(cout, 0x0C, " lost!");
					cout << endl << endl << "the word was '" << passcode << "'" << endl;
					break;
				}
			}

			if (!memcmp(passcode, passcodeDisplay, passcodeLength))
			{
				cout << players[playerIndex].name;
				PrintColor(cout, 0x0A, " won!!!");
				cout << endl << endl << players[playerIndex].name << " correctly guessed the word '" << passcode << "'" << endl;
				break;
			}
		}

		players[playerIndex].playTime = time(0) - timeStart;
		cout << "It took " << players[playerIndex].playTime << " seconds for " << players[playerIndex].name << " to finish." << endl;
		system("pause");


		delete[] passcodeDisplay;
		delete[] passcode;
	}


}

void SaveResults(Player* players)
{
	stringstream html;

	html << "<html><head><style>"
		"table {border-collapse:collapse;}"
		"td, th {border: 1px solid black}"
		"</style></head><body><table><tr><th>Tekmovalec</th><th>Geslo</th><th>Stevilo Ugibanj</th><th>Cas</th></tr>";

	for (UINT i = 0; i < playerCount; ++i)
	{
		html << 
			"<tr><td>" << players[i].name <<
			"</td><td>\"" << players[i].currentPasscode <<
			"\"</td><td>" << players[i].passcodeHistory.size() << 
			"</td><td>" << players[i].playTime << "s</td></tr>";
	}

	html << "</table></body></html>";

	ofstream file("results.htm");

	if (file.is_open())
	{
		file << html.str();

		file.close();
	}
}

void main()
{
	string passcodes[passcodeCount];
	LoadPasscodes(passcodes);

	string scenes[sceneCount];
	LoadScenes(scenes);

	Player players[playerCount];
	LoadPlayers(players);

	srand((UINT)time(0));
	GameLoop(passcodes, scenes, players);

	SaveResults(players);
}