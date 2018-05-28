#pragma once
#include <string>
#include "Date.h"

typedef unsigned int uint;
class Account
{
private:
	static uint count;
	static uint active;

protected:
	uint id;
	std::string name;
	uint age;
	std::string username;
	std::string password;
	Date* birthday;

public:
	Account();
	Account(const Account& account);
	Account(std::string name, uint age, std::string username, std::string password, Date* birthday);
	~Account();

	uint getID() const;

	std::string getName() const;
	void setName(const std::string& name);

	uint getAge() const;
	void setAge(uint age);

	std::string getUsername() const;
	void setUsername(const std::string& username);

	std::string getPassword() const;
	void setPassword(const std::string& password);

	Date* getBirthday() const;
	void setBirthday(Date* birthday);

	std::string toString() const;

	static uint GetActiveCount();
	static std::string suggestUsername();
	static Account GetDemoAccount();
	void resetPassword();

	bool isEqual(const Account& second) const;
};
