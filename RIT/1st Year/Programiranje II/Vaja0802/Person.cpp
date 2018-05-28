#include "Person.h"
#include <sstream>

Person::Person(std::string name, uint age, Date birthday) :
	name(name),
	age(age),
	birthday(birthday)
{
}

Person::Person(const Person & c) : Person(c.name, c.age, c.birthday)
{
}

std::string Person::getName() const
{
	return name;
}

void Person::setName(const std::string name)
{
	this->name = name;
}

uint Person::getAge() const
{
	return age;
}

void Person::setAge(const uint age)
{
	this->age = age;
}

Date Person::getBirthday() const
{
	return birthday;
}

void Person::setBirthday(const Date& birthday)
{
	this->birthday = birthday;
}

std::string Person::toString() const
{
	std::stringstream ss;
	ss << "{ name=" << name << "; age=" << age << "; birthday=" << birthday << " }";
	return ss.str();
}

bool Person::isEqual(const Person& p) const
{
	return name == p.name && age == p.age && birthday == p.birthday;
}

bool Person::operator==(const Person& d) const
{
	return isEqual(d);
}

std::string Person::toJSON()
{
	std::stringstream ss;
	ss << "{ \"name\": \"" << name << "\", \"age\": " << age << ", \"birthday\": " << birthday.toJSON() << " }";
	return ss.str();
}
