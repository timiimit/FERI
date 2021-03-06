#include <iostream>
using namespace std;

typedef unsigned long long ULONG;
typedef long long LONG;

LONG f1(LONG a, LONG b);
int f2();
float f3(int polje[], int count);
void f4(int polje[], int count);
void f5(int polje[], int count);


void main()
{
	LONG a;
	LONG b;
	cout << "vpisi prvo stevilo: ";
	cin >> a;
	cout << "vpisi drugo stevilo: ";
	cin >> b;

	LONG res = f1(a, b);
	if (res <= 0)
		cout << "zal ta program ni dovolj sposoben da bi nasel tako veliki majmanjsi skupni veckratnik ali pa je prislo do napake" << endl;
	else
		cout << "najmanjsi skupni veckratnik teh dveh stevil je " << res << endl;

	const int MAXCOUNT = 1024;
	int arr[MAXCOUNT];
	cout << "mediana vseh stevil ki so deljiva s 7 in so med 200 in 3000 je " << f3(arr, MAXCOUNT) << endl;
	system("pause");
}

// a) Napišite funkcijo f1, ki prejme dve celi števili in vrne dvakratnik najmanjšega skupnega večkratnika.
LONG f1(LONG a, LONG b)
{
	if (a <= 0 || b <= 0)
	{
		return -1;
	}

	LONG multipliera = 1;
	LONG multiplierb = 1;

	while (true)
	{
		LONG x = a * multipliera;
		LONG y = b * multiplierb;

		if (x < a || x < 0 || y < b || y < 0 || multipliera <= 0 || multiplierb <= 0)
			return -3;

		if (x < y)
		{
			multipliera++;
		}
		else if (x > y)
		{
			multiplierb++;
		}
		else
		{
			if (x % a == 0 && x % b == 0)
				return x;
			return -2;
		}
	}
}

// b) Napišite funkcijo f2, ki izračuna in vrne, koliko števil je deljivih s številom 7 v razponu od vključno 300 do vključno 2000.
int f2()
{
	int count = 0;
	for (int i = 300; i <= 2000; ++i)
	{
		if (i % 7 == 0)
		{
			count++;
		}
	}

	return count;
}

// c) Napišite funkcijo f3, ki prejme kot argument polje celih števil in velikost polja.
// Funkcija napolni polje s števili, ki so deljiva s številom 7 v razponu od vključno 300 do vključno 2000 in vrne mediano polja.
float f3(int polje[], int count)
{
	int index = 0;
	for (int i = 300; i <= 2000 && index < count; ++i)
	{
		if (i % 7 == 0)
		{
			polje[index] = i;
			index++;
		}
	}
	if (index & 1)
	{
		// odd
		return (float)polje[index / 2];
	}
	else
	{
		// even
		return (float)(polje[index / 2] + polje[index / 2 + 1]) / 2.0f;
	}
}

// d) Napišite funkcijo f4 za izpis števil na sodih indeksih (tudi indeks 0) od leve proti desni.
void f4(int polje[], int count)
{
	for (int i = 0; i < count; i += 2)
	{
		cout << polje[i] << " ";
	}
	cout << endl;
}

// e) Napišite funkcijo f5 za izpis števil na lihih indeksih od desne proti levi.
void f5(int polje[], int count)
{
	for (int i = (count - 1 & 1 ? count - 1 : count - 2); i >= 1; i -= 2)
	{
		cout << polje[i] << " ";
	}
	cout << endl;
}