#pragma once
#include <string>

typedef unsigned int uint;
class Account
{
private:
	std::string name;
	uint age;
	std::string username;
	std::string password;

public:
	Account();
	Account(const Account& account);
	Account(std::string name, uint age, std::string username, std::string password);
	~Account();

	std::string getName();
	void setName(const std::string& name);

	uint getAge();
	void setAge(uint age);

	std::string getUsername();
	void setUsername(const std::string& username);

	std::string getPassword();
	void setPassword(const std::string& password);

	std::string toString();

	static std::string suggestUsername();
	void resetPassword();

};