#include "Date.h"
#include <sstream>

Date::Date() : Date(0, 0, 0)
{
}

Date::Date(const Date& date) : Date(date.year, date.month, date.day)
{
}

Date::Date(uint year, uint month, uint day) :
	year(year),
	month(month),
	day(day)
{
}

Date::~Date()
{
}

uint Date::getYear() const
{
	return year;
}

void Date::setYear(uint year)
{
	this->year = year;
}

uint Date::getMonth() const
{
	return month;
}

void Date::setMonth(uint month)
{
	this->month = month;
}

uint Date::getDay() const
{
	return day;
}

void Date::setDay(uint day)
{
	this->day = day;
}

std::string Date::toString() const
{
	std::stringstream ss;
	ss << day << '/' << month << '/' << year;
	return ss.str();
}

bool Date::isOlder(Date d) const
{
	if (year > d.year)
		return true;
	else if (year == d.year)
	{
		if (month > d.month)
			return false;
		else if (month == d.month)
		{
			if (day > d.day)
				return true;
		}
	}
	return false;
}

bool Date::operator==(const Date & d) const
{
	return
		year == d.year &&
		month == d.month &&
		day == d.day;
}

std::ostream& operator<<(std::ostream& stream, const Date& date)
{
	stream << date.day << "/" << date.month << "/" << date.year;
	return stream;
}

bool isOlder(Date d1, Date d2)
{
	return d1.isOlder(d2);
}

void sort(Date** dates, int dateCount)
{
	for (int i = 0; i < dateCount; i++)
	{
		for (int j = 0; j < dateCount; j++)
		{
 			if (dates[i]->isOlder((*(dates[j]))))
			{
				Date* tmp = dates[i];
				dates[i] = dates[j];
				dates[j] = tmp;
			}
		}
	}
} 
