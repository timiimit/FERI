#pragma once
#include <string>
#include <ostream>

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

	uint getYear() const;
	void setYear(uint year);

	uint getMonth() const;
	void setMonth(uint month);

	uint getDay() const;
	void setDay(uint day);

	std::string toString() const;
	bool isOlder(Date d) const;

	bool operator==(const Date& d) const;
	friend std::ostream& operator<<(std::ostream& stream, const Date& date);
};

bool isOlder(Date d1, Date d2);
void sort(Date** dates, int dateCount);
