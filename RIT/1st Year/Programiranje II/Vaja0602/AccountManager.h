#pragma once
#include "Account.h"
#include <string>

class AccountManager
{
private:
	class Node
	{
	public:
		Account* account;
		Node* next;

		Node() :
			account(nullptr),
			next(nullptr)
		{
		}

		Node(Account* account) :
			account(account),
			next(nullptr)
		{
		}

		~Node()
		{
		}
	};

	Node* first;
	int size;

public:

	AccountManager();
	AccountManager(const AccountManager& a);
	~AccountManager();

	int getSize() const;
	void addElement(Account& account);
	Account* getElementAt(int index) const;
	void changeUsername(int index, std::string username) const;
	void changePassword(int index, std::string password) const;
	void removeElementAt(int index) const;
	int findByUsername(std::string username) const;
};