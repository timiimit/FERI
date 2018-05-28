//============================================================================
// Name        : Naloga0102.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <time.h>
#include <string>

using namespace std;

typedef unsigned int uint;

uint menu()
{
	cout << endl;
	cout << "Menu\n";
	cout << "=========\n";
	cout << "5. SORTIRAJ\n";
	cout << "4. NAJMANJSA STAROST\n";
	cout << "3. POLNOLETNE OSEBE\n";
	cout << "2. POVPRECNA STAROST\n";
	cout << "1. GENERIRANJE STAROSTI\n";
	cout << "0. IZHOD IZ PROGRAMA\n";
	cout << "=========\n";
	cout << "Izberi: ";

	while (true)
	{
		string buf;
		cin >> buf;
		if (buf.length() == 1)
		{
			return (uint)(buf[0] - '0');
		}
	}
}

void Sort(uint* ages, uint count)
{
	for (uint i = 0; i < count; ++i)
	{
		for (uint j = 0; j < count; ++j)
		{
			if (ages[i] < ages[j])
			{
				uint tmp = ages[i];
				ages[i] = ages[j];
				ages[j] = tmp;
			}
		}
	}
}

uint GetLowestAge(uint* ages, uint count)
{
	uint min = -1;
	for (int i = 0; i < count; i++)
	{
		if (ages[i] < min)
			min = ages[i];
	}
	return min;
}

uint GetLegalAgeCount(uint* ages, uint count)
{
	uint legalcount = 0;
	for (int i = 0; i < count; i++)
	{
		if (ages[i] >= 18)
			legalcount++;
	}
	return legalcount;
}

uint GetAverageAge(uint* ages, uint count)
{
	uint sum = 0;
	for (uint i = 0; i < count; ++i)
	{
		sum += ages[i];
	}
	return sum / count;
}

void napolniPoljeStevil(uint* starost, int n)
{
	for (int index = 0; index < n; index++)
	{
		starost[index] = (rand() % 81) + 8;
	}
}

void izpisiPoljeStevil(uint* starost, int n)
{
	for (int index = 0; index < n; index++)
	{
		cout << starost[index] << " ";
	}
}

int main(int argc, char *argv[])
{
	const uint n = 20;
	uint starost[n];

	bool running = true;

	while (running)
	{
		uint izbira = menu();
		switch (izbira)
		{
			case 5:
				Sort(starost, n);
				cout << "Polje stevil:" << endl;
				izpisiPoljeStevil(starost, n);
				cout << endl;
				break;

			case 4:
				cout << GetLowestAge(starost, n) << endl;
				break;

			case 3:
				cout << GetLegalAgeCount(starost, n) << endl;
				break;

			case 2:
				cout << GetAverageAge(starost, n) << endl;
				break;

			case 1:
				napolniPoljeStevil(starost, n);
				cout << "Polje stevil:" << endl;
				izpisiPoljeStevil(starost, n);
				cout << endl;
				break;

			case 0:
				running = false;
				break;

			default:
				cout << "Napacna izbira!\n";
		}
	}
	return 0;
}