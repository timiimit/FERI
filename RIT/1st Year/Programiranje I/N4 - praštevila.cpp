#include <iostream>
#include <math.h>
using namespace std;

bool jePrastevilo(int x);
int getPrasteviloCount();
float getAveragePrastevilo20(int a[], int start);

// the way it was maybe thought but not written
void main()
{
	// nikjer ne pise da moremo v programu uporabit 2. funkcijo (getPrasteviloCount) ampak jo bom vseeno za vsak slucaj da se vidi da jo znam uporabit
	int result = getPrasteviloCount();

	int nums[20];
	int x;

	cout << "enter 1st number: ";
	cin >> x;

	getAveragePrastevilo20(nums, x);

	cout << "enter 2nd number: ";
	cin >> x;

	double sqrtx = sqrt(x);
	int minDistIndex = 0;
	for (int i = 1; i < 20; ++i)
	{
		if (abs(nums[i] - sqrtx) < abs(nums[minDistIndex] - sqrtx))
		{
			minDistIndex = i;
		}
	}

	cout << "Closest prime to sqrt of " << x << " from list of 20 primes is " << nums[minDistIndex] << endl;
	system("pause");
}

// the way its cool but not written
//void main()
//{
//	cout << "enter any number: ";
//	double num;
//	cin >> num;
//
//	const int SIZE = 20;
//	int a[SIZE];
//	float average = getAveragePrastevilo20(a, num);
//	
//	double sqrtnum = sqrt(num);
//	int intsqrtnum = (int)sqrtnum;
//	int i = 0;
//	while (true)
//	{
//		int plus = intsqrtnum + i + 1;
//		int minus = intsqrtnum - i;
//
//		bool up = jePrastevilo(plus);
//		bool down = jePrastevilo(minus);
//		if (up && down)
//		{
//			if ((double)(plus) - sqrtnum > sqrtnum - (double)(minus))
//			{
//				up = false;
//			}
//			else if ((double)(plus) - sqrtnum < sqrtnum - (double)(minus))
//			{
//				down = false;
//			}
//			else
//			{
//				// enako oddaljeno stevilo
//				// idk what to do
//				int breakpoint = 0;
//			}
//
//		}
//
//
//		if (up && down)
//		{
//			cout << "omg obstajata dve prastevili ki sta enako oddaljeni korenu stevila " << num << " (" << sqrtnum << ") sta " << plus << " in " << minus << endl;
//			break;
//		}
//		else if (up)
//		{
//			cout << "najblizje prastevilo korenu stevila " << num << " (" << sqrtnum << ") je " << plus << endl;
//			break;
//		}
//		else if (down)
//		{
//			cout << "najblizje prastevilo korenu stevila " << num << " (" << sqrtnum << ") je " << minus << endl;
//			break;
//		}
//		i++;
//	}
//
//	system("pause");
//}

bool jePrastevilo(int x)
{
	if (x <= 1)
		return false;
	else if (x == 2)
		return true;
	else if (x % 2 == 0)
		return false;

	double half = sqrt(x);
	for (int i = 3; i <= half; i += 2)
	{
		if (x % i == 0)
		{
			return false;
		}
	}
	return true;
}

int getPrasteviloCount()
{
	int count = 0;
	//-217 do vključno 9001
	for (int i = -217; i <= 9001; ++i)
	{
		if (jePrastevilo(i))
			count++;
	}
	return count;
}

float getAveragePrastevilo20(int a[], int start)
{
	float sum = 0;
	int count = 0;
	while (count < 20)
	{
		if (jePrastevilo(start))
		{
			a[count] = start;
			sum += start;
			count++;
		}
		start++;
	}

	return sum / 20;
}

