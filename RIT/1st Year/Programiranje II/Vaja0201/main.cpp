#include "Tocka.h"
#include <iostream>

using namespace std;

bool pozitivna(const Tocka& t)
{
	return t.getX() > 0 && t.getY() > 0;
}


void specialprint(const Tocka& pt)
{
	pt.print();
	std::cout << " is " << (pozitivna(pt) ? "positive" : "negative") << std::endl;
}

void main()
{
	Tocka staticPt;
	staticPt.print();
	cout << endl;

	Tocka* dynamicPt = new Tocka(1, 4);
	specialprint(*dynamicPt);

	Tocka flipped = dynamicPt->vrniZrcalnoTockoX();
	specialprint(flipped);

	delete dynamicPt;

	system("pause");
}