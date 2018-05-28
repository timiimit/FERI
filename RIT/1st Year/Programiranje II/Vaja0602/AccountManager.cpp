#include "AccountManager.h"

AccountManager::AccountManager() : 
	first(nullptr),
	size(0)
{
}

AccountManager::AccountManager(const AccountManager& a) :
	size(a.size)
{
	if (size > 0)
	{
		first = new Node(new Account(*a.first->account));
	}
	Node* tmp = first;
	Node* tmp2 = a.first;
	while (tmp)
	{
		tmp->account = new Account(*tmp2->account);

		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
}

AccountManager::~AccountManager()
{
	Node* tmp = first;
	while (tmp)
	{
		Node* next = tmp->next;
		delete tmp->account;
		delete tmp;
		tmp = next;
	}
}

int AccountManager::getSize() const
{
	return size;
}

void AccountManager::addElement(Account& account)
{
	Node* tmp = first;
	if (!tmp)
	{
		first = new Node(new Account(account));
		return;
	}
	while (tmp->next)
		tmp = tmp->next;

	tmp->next = new Node(new Account(account));
}

Account* AccountManager::getElementAt(int index) const
{
	if (index < size)
		throw std::exception();

	Node* tmp = first;
	for (int i = 0; i < index; i++)
	{
		tmp = tmp->next;
	}
	return tmp->account;
}

void AccountManager::changeUsername(int index, std::string username) const
{
	if (index < size)
		throw std::exception();

	Node* tmp = first;
	for (int i = 0; i < index; i++)
	{
		tmp = tmp->next;
	}
	return tmp->account->setUsername(username);
}

void AccountManager::changePassword(int index, std::string password) const
{
	if (index < size)
		throw std::exception();

	Node* tmp = first;
	for (int i = 0; i < index; i++)
	{
		tmp = tmp->next;
	}
	return tmp->account->setPassword(password);
}

void AccountManager::removeElementAt(int index) const
{
	if (index < size)
		throw std::exception();

	Node* tmp = first;
	for (int i = 0; i < index-1; i++)
	{
		tmp = tmp->next;
	}
	Node* next = tmp->next->next;
	delete tmp->next->account;
	delete tmp->next;
	tmp->next = next;
}

int AccountManager::findByUsername(std::string username) const
{
	Node* tmp = first;
	int index = -1;
	while (tmp)
	{
		index++;
		if (tmp->account->getUsername() == username)
			return index;

		tmp = tmp->next;
	}
	return index;
}
