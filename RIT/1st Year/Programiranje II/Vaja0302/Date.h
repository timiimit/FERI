#pragma once
#include <string>

typedef unsigned int uint;

class Date
{
private:
	uint year;
	uint month;
	uint day;

public:
	Date();
	Date(const Date& date);
	Date(uint year, uint month, uint day);
	~Date();

	uint getYear();
	void setYear(uint year);

	uint getMonth();
	void setMonth(uint month);

	uint getDay();
	void setDay(uint day);

	std::string toString();
	bool isOlder(Date d);
};

bool isOlder(Date d1, Date d2);
void sort(Date** dates, int dateCount);