#include <iostream>
#include "Account.h"
#include <time.h>

using namespace std;

bool usernameExists(Account* userAccount, Account** accounts, int accountCount)
{
	for (int i = 0; i < accountCount; i++)
	{
		if (userAccount->getUsername() == accounts[i]->getUsername())
		{
			return true;
		}
	}
	return false;
}

// https://stackoverflow.com/questions/13155474/difference-between-static-and-non-static-members
// http://www.geekinterview.com/question_details/122

void main()
{
	srand((uint)time(0));
	int accountCount = 5;
	Account** accounts = new Account*[accountCount];

	while (true)
	{
		cout << "MENU" << endl
			<< "0 Exit" << endl
			<< "1 Fill accounts" << endl
			<< "2 Print account information" << endl
			<< "3 New username" << endl
			<< "4 Reset password" << endl
			<< "5 Does username exists" << endl;

		string input;
		cin >> input;

		system("cls");

		if (input.length() != 1)
		{
			continue;
		}

		int selection = input[0] - '0';

		switch (selection)
		{
			case 0:
				break;

			case 1:
				for (int i = 0; i < accountCount; i++)
				{
					accounts[i] = new Account(Account::GetDemoAccount());
				}
				continue;

			case 2:
			case 3:
			case 4:
			{
				cout << "Enter Account ID: ";
				string strnumber;
				cin >> strnumber;
				int accid = stoi(strnumber);
				if (accid >= 0 && accid <= accountCount)
				{
					switch (selection)
					{
						case 2:
							cout << accounts[accid]->toString() << endl;
							break;

						case 3:
							while (true)
							{
								system("cls");
								string suggestion = Account::suggestUsername();
								cout << "New username suggestion: " << suggestion << endl << endl;
								cout << "0 Exit username generation" << endl
									<< "1 Suggest another username" << endl
									<< "2 Set suggested username and exit" << endl;

								cin >> strnumber;
								int number = stoi(strnumber);
								if (number >= 0 && number <= 2)
								{
									switch (number)
									{
										case 0:
											break;

										case 1:
											continue;

										case 2:
											accounts[accid]->setUsername(suggestion);;
											break;
									}
									break;
								}
							}
							break;

						case 4:
							accounts[accid]->resetPassword();
							break;
					}
				}
				else
				{
					cout << "Account with that id does not exist." << endl;
				}
				continue;
			}

			case 5:
				cout << "Check if which user exists? ";
				string username;
				cin >> username;

				Account a("", 0, username, "");
				cout << "Chosen username does " << (usernameExists(&a, accounts, accountCount) ? "" : "not ") << "exist" << endl;
				continue;

		}
		break;
	}

}