#include "Horse.h"
#include <iostream>

using namespace std;

void main()
{
	const int count = 10;
	Horse horses[count];
	horses[5].SetName("Hugo");
	horses[5].SetSpeed(24.0f);
	cout << horses[5].GetName() << " can run " << horses[5].GetSpeed() << " mph" << endl;
	system("pause");
}

// Class: Car(brandname, modelversion, topspeed, timeto100mps) estimateTravelDistancePerTime(float time)
// Class: Ucenec(ime, sola, vlozentrud) vrniECTS()
// Class: Urnik(sola) dodajPredavanjaNaUrnik(const Ucilnica& ucilnica, const Profesor& prof, const DateTime& zacetek, const DateTime& konec)