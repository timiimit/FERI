#include "Vetrnica.h"
#include <iostream>

using namespace std;

Vetrnica::Vetrnica() :
	stKrakov(2),
	sirinaKrakov(0.2f),
	dolzinaKrakov(1.5f),
	lastnik()
{
}

Vetrnica::Vetrnica(const Vetrnica& c) :
	stKrakov(c.stKrakov),
	sirinaKrakov(c.sirinaKrakov),
	dolzinaKrakov(c.dolzinaKrakov),
	lastnik(c.lastnik)
{
}

Vetrnica::~Vetrnica()
{
}

int Vetrnica::getSteviloKrakov() const
{
	return stKrakov;
}

void Vetrnica::setSteviloKrakov(int nStKrakov)
{
	stKrakov = nStKrakov;
}

float Vetrnica::getSirinaKrakov() const
{
	return sirinaKrakov;
}

void Vetrnica::setSirinaKrakov(float nSirinaKrakov)
{
	sirinaKrakov = nSirinaKrakov;
}

float Vetrnica::getDolzinaKrakov() const
{
	return dolzinaKrakov;
}

void Vetrnica::setDolzinaKrakov(float nDolzinaKrakov)
{
	dolzinaKrakov = nDolzinaKrakov;
}

std::string Vetrnica::getLastnik() const
{
	return lastnik;
}

void Vetrnica::setLastnik(std::string nLastnik)
{
	lastnik = nLastnik;
}

void Vetrnica::izpis() const
{
	cout << toString() << endl;
}

std::string Vetrnica::toString() const
{
	string s;
	s += "Lastnik: " + lastnik;
	s += "\nStevilo Krakov: " + stKrakov;
	s += "\nSirina Krakov: ";
	s += sirinaKrakov;
	s += "\nDolzina Krakov: ";
	s += dolzinaKrakov;
	return s;
}

void Vetrnica::read()
{
	cout << "Lastnik: ";
	cin >> lastnik;

	cout << "Stevilo Krakov: ";
	cin >> stKrakov;

	cout << "Sirina Krakov: ";
	cin >> sirinaKrakov;

	cout << "Dolzina Krakov: ";
	cin >> dolzinaKrakov;
}