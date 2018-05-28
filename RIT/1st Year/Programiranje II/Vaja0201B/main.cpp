#include "Vetrnica.h"
#include <iostream>

using namespace std;

void main()
{
	Vetrnica v;
	v.read();

	Vetrnica cpy(v);
	cout << "Kopija originalne Vetrnice ima lastnika '" + cpy.getLastnik() + "'" << endl;
	cout << "Kopija originalne Vetrnice ima " << cpy.getSteviloKrakov() << " krakov" << endl;
	cout << "Kopija originalne Vetrnice ima krake sirine " << cpy.getSirinaKrakov() <<  " metrov" << endl;
	cout << "Kopija originalne Vetrnice ima krake dolzine " << cpy.getDolzinaKrakov() << " metrov" << endl;
	system("pause");
}