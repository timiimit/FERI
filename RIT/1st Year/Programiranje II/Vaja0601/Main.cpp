#include "VerifiedAccount.h"
#include "Date.h"
#include <iostream>

using namespace std;

void main()
{
	Date* d = new Date(1998, 3, 29);
	VerifiedAccount vacc = VerifiedAccount("timiimit", 20, "timiimit", "pass123", d, VerificationType::email, "succesful", Date(2016, 5, 23));
	cout << vacc.toString() << endl;
	delete d;

	system("pause");
}

// primeri:
// dedovanje - bitmapheader v2 : bitmapheader v1
// dedovanje - zebra : zival
// agregacija/kompozicija - Player { Armor; Weapon; }
// agregacija/kompozicija - Avto { Voznik; }