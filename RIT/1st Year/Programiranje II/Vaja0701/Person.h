#pragma once
#include <string>
#include "Date.h"

class Person
{
private:
	std::string name;
	uint age;
	Date birthday;

public:

	Person(std::string name, uint age, Date birthday);
	Person(const Person& c);

	std::string getName() const;
	void setName(const std::string name);

	uint getAge() const;
	void setAge(const uint age);

	Date getBirthday() const;
	void setBirthday(const Date& birthday);

	std::string toString() const;
	bool isEqual(const Person& p) const;

	bool operator==(const Person& d) const;
};