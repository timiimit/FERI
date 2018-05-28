#include "Account.h"
#include <sstream>

using namespace std;

Account::Account() : Account("", -1, "", "")
{
}

Account::Account(const Account& account) : Account(account.name, account.age, account.username, account.password)
{
}

Account::Account(std::string name, uint age, std::string username, std::string password) :
	name(name),
	age(age),
	username(username),
	password(password)
{
}

Account::~Account()
{
	// no deletion needed
	// because of usage of string
}

std::string Account::getName()
{
	return name;
}

void Account::setName(const std::string& name)
{
	this->name = name;
}

uint Account::getAge()
{
	return age;
}

void Account::setAge(uint age)
{
	this->age = age;
}

std::string Account::getUsername()
{
	return username;
}

void Account::setUsername(const std::string& username)
{
	this->username = username;
}

std::string Account::getPassword()
{
	return password;
}

void Account::setPassword(const std::string& password)
{
	this->password = password;
}


std::string Account::toString()
{
	stringstream ss;
	ss << "{ Name: " <<  name << " " << "Age: " << age << " Username: " << username << "}";
	return ss.str();
}

#ifndef ARRAYSIZE 
#define ARRAYSIZE(x) sizeof(x) / sizeof(*x)
#endif

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
