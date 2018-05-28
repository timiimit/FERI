#include <string>
#include <iostream>
#include <time.h>
#include "AccountManager.h"

using namespace std;

void main()
{
	srand((uint)time(0));
	int accountCount = 5;
	AccountManager accounts;

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
					Account a = Account(Account::GetDemoAccount());
					accounts.addElement(a);
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
							cout << accounts.getElementAt(accid)->toString() << endl;
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
											accounts.getElementAt(accid)->setUsername(suggestion);;
											break;
									}
									break;
								}
							}
							break;

						case 4:
							accounts.getElementAt(accid)->resetPassword();
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

				cout << "Chosen username does " << (accounts.findByUsername(username) != -1 ? "" : "not ") << "exist" << endl;
				continue;

		}
		break;
	}
}