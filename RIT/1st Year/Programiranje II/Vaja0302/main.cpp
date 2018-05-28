#include "Date.h"
#include <iostream>
#include <random>

using namespace std;

void main()
{
	int dateCount = 10;
	Date** dates = new Date*[dateCount];
	for (int i = 0; i < dateCount-2; i++)
	{
		dates[i] = new Date(2000 + rand() % 20, rand() % 13, rand() % 32);
	}

	dates[dateCount - 1 - 1] = new Date();
	dates[dateCount - 1] = new Date(**dates); // copy 1st Date
	dates[dateCount - 1]->setYear(2018);
	dates[dateCount - 1]->setMonth(2);
	dates[dateCount - 1]->setDay(4);
	sort(dates, dateCount);

	for (int i = 0; i < dateCount; i++)
	{
		cout << dates[i]->toString() << endl;
	}
	system("pause");
}