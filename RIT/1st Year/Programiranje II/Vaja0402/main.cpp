#include "Besedilo.h"
#include <iostream>

using namespace std;

void main()
{
	Besedilo b;
	cout
		<< "length: " << b.GetLength() << endl
		<< "text: " << endl << '\'' << b.toString() << '\'' << endl << endl << "text above " << (b.jePodniz(0, "one") ? "contains" : "does not contain") << " the word 'one' in 1st line" << endl
		<< "samoglasnikov je " << b.prestejSamoglasnike() << endl
		<< "besed je " << b.prestejSteviloBesed() << endl
		<< Besedilo::NizVStevilo("123") << endl
		<< Besedilo::NizVFloat("-1.4") << endl
		<< Besedilo::VeljavniEmail("test@gmail.com") << endl;
	system("pause");
}