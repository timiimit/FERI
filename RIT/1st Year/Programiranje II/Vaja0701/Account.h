#pragma once
#include <string>
#include "Date.h"
#include "Person.h"

typedef unsigned int uint;
class Account
{
private:
	static uint count;
	static uint active;

protected:
	uint id;
	std::string username;
	std::string password;
	Person* person;

public:
	Account();
	Account(const Account& account);
	Account(const std::string name, const uint age, const std::string username, const std::string password, const Date& birthday);
	~Account();

	uint getID() const;

	std::string getUsername() const;
	void setUsername(const std::string& username);

	std::string getPassword() const;
	void setPassword(const std::string& password);

	const Person& getPerson() const;
	void setPerson(const Person& person);

	static uint GetActiveCount();
	static std::string suggestUsername();
	static Account GetDemoAccount();
	void resetPassword();

	virtual std::string toString() const;
	virtual bool isEqual(const Account& second) const;
	std::string toStringNV() const;
	bool isEqualNV(const Account& second) const;
};
