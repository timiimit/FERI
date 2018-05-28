#include "Account.h"
#include <sstream>

using namespace std;

uint Account::count(1000);
uint Account::active(0);

Account::Account() : Account("", -1, "", "", Date())
{
}

Account::Account(const Account& account) : Account(account.person->getName(), account.person->getAge(), account.username, account.password, account.person->getBirthday())
{
}

Account::Account(const std::string name, const uint age, const std::string username, const std::string password, const Date& birthday) :
	person(new Person(name, age, birthday)),
	username(username),
	password(password),
	id(count)
{
	count++;
	active++;
}

Account::~Account()
{
	delete person;
	active--;
}


std::string Account::getUsername() const
{
	return username;
}

void Account::setUsername(const std::string& username)
{
	this->username = username;
}

std::string Account::getPassword() const
{
	return password;
}

void Account::setPassword(const std::string& password)
{
	this->password = password;
}

const Person& Account::getPerson() const
{
	return *person;
}

void Account::setPerson(const Person& p)
{
	*this->person = p;
}

#ifndef ARRAYSIZE 
#define ARRAYSIZE(x) sizeof(x) / sizeof(*x)
#endif

uint Account::GetActiveCount()
{
	return Account::active;
}

std::string Account::suggestUsername()
{
	const char* adj[] = { "fast", "sharp", "strong", "flashy", "best", "junkie", "chosen", "happy", "sad", "unlucky" };
	const uint adjlen = ARRAYSIZE(adj);

	const char* dog[] = { "george", "rusty", "storm", "flash", "maximus", "diva", "chelsea", "joey", "ace", "mickey" };
	const uint doglen = ARRAYSIZE(dog);

	const char* sep[] = { "", ".", "_" };
	const uint seplen = ARRAYSIZE(sep);

	const uint maxnum = 100;

	uint iadj = rand() % adjlen;
	uint isep = rand() % seplen;
	uint idog = rand() % doglen;
	bool addnum = rand() % 2;

	stringstream ss;
	ss << adj[iadj];
	ss << sep[isep];
	ss << dog[idog];
	if (addnum)
	{
		uint rnum = rand() % (maxnum + 10); // +10 allows zero padded numbers
		if (rnum >= maxnum)
		{
			rnum -= maxnum;
			if (rnum < 10)
			{
				ss << 0;
			}
		}
		ss << rnum;
	}
	return ss.str();
}

Account Account::GetDemoAccount()
{
	Account a;
	a.setUsername(suggestUsername());
	a.resetPassword();
	return a;
}

void Account::resetPassword()
{
	string str;
	uint count = 6 + (rand() % 3);
	for (uint i = 0; i < count; i++)
	{
		if (rand() % 2)
		{
			str += 'A' + (rand() % (1 + 'Z' - 'A'));
		}
		else
		{
			str += 'a' + (rand() % (1 + 'z' - 'a'));
		}
	}
	password = str;
}

std::string Account::toString() const
{
	stringstream ss;
	ss << "{ Person*: " << person->toString() << " " << " Username: " << username << "}";
	return ss.str();
}

bool Account::isEqual(const Account& second) const
{
	return
		id == second.id &&
		username == second.username &&
		password == second.password &&
		*person == *second.person;
}

std::string Account::toStringNV() const
{
	stringstream ss;
	ss << "{ Person*: " << person->toString() << " " << " Username: " << username << "}";
	return ss.str();
}

bool Account::isEqualNV(const Account & second) const
{
	return
		id == second.id &&
		username == second.username &&
		password == second.password &&
		*person == *second.person;
}

std::string Account::toJSON()
{
	std::stringstream ss;
	ss << "{ \"id\": " << id << ", \"username\": \"" << username << "\", \"password\": \"" << password << "\", \"person\":" << person->toJSON() << " }";
	return ss.str();
}
