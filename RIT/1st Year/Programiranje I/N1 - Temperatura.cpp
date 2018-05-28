#include <iostream>
using namespace std;

void main()
{
	int a[] = { 10, 17, 20, 36, 10, 14, 4, 17, 2, 17, 2, 17, 4, 15, 7, 10 };
	int count = sizeof(a) / sizeof(int);
	if ((count & 1) == 1)
		cout << "liho stevilo stevil" << endl;
	for (int i = 0; i < count; i++)
	{
		if (a[i] < 12)
		{
			cout << "#, ";
		}
		else
		{
			wcout << a[i] << ", ";
		}

		i++;

		if (a[i] > 35)
		{
			cout << "?" << endl;
		}
		else
		{
			cout << a[i] << endl;
		}
	}
	getchar();
}