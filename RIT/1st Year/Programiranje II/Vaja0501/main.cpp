#pragma once
#include <iostream>
#include <string>
#include <sstream>


class Snov
{
private:
	std::string ime;
	double masa;
	double gostota;
	double volumen;
	unsigned tip;

	static double calcVolume(double mass, double density)
	{
		return density / mass;
	}

public:

	static const unsigned KAPLJEVINA = 1;
	static const unsigned TRDA_SNOV = 2;
	static const unsigned PLIN = 3;

	Snov() : Snov("voda", 1000, 1000, KAPLJEVINA)
	{
	}

	Snov(const Snov& cpy) : Snov(cpy.ime, cpy.masa, cpy.gostota, cpy.tip)
	{
	}

	Snov(std::string ime, double masa, double gostota, unsigned tip) :
		ime(ime),
		masa(masa),
		gostota(gostota),
		volumen(calcVolume(gostota, masa)),
		tip(tip)
	{
	}

	std::string getIme()
	{
		return ime;
	}
	void setIme(std::string ime)
	{
		this->ime = ime;
	}

	double getMasa()
	{
		return masa;
	}
	void setMasa(double masa)
	{
		this->masa = masa;
		volumen = calcVolume(masa, gostota);
	}

	double getGostota()
	{
		return gostota;
	}
	void setGostota(double gostota)
	{
		this->gostota = gostota;
		volumen = calcVolume(masa, gostota);
	}

	double getVolumen()
	{
		return volumen;
	}

	unsigned getTip()
	{
		return tip;
	}
	void setTip(unsigned tip)
	{
		this->tip = tip;
	}

	std::string toString()
	{
		std::stringstream ss;
		ss << "{ ime = " << ime << "; masa = " << masa << "; gostota = " << gostota << "; volumen = " << volumen << "; tip = " << (tip == 1 ? "KAPLJEVINA" : (tip == 2 ? "TRDA_SNOV" : (tip == 3 ? "PLIN" : "NEZNAN_TIP"))) << "; }";
		return ss.str();
	}

	bool gostejsa(Snov* druga)
	{
		return druga->gostota > gostota;
	}

	bool jeGostejsaOdVode()
	{
		return gostota > 1000;
	}

	static Snov* Najgostejsa(Snov** listaSnovi, int velikostListe)
	{
		Snov** end = listaSnovi + velikostListe;
		Snov* max = *listaSnovi;
		listaSnovi++;
		while (listaSnovi < end)
		{
			if ((*listaSnovi)->gostota > max->gostota)
				max = *listaSnovi;
			listaSnovi++;
		}
		return max;
	}
};

int steviloTezjihOdVode(Snov** snovi, int count)
{
	int counter = 0;
	Snov** end = snovi + count;
	while (snovi < end)
	{
		if ((*snovi)->getGostota() > 1000)
			counter++;
		snovi++;
	}
	return counter;
}

void main()
{
	using namespace std;

	int count = 5;
	//int** test = new int*[count]{ new int(10), new int(1) }; // works!!
	Snov** snovi = new Snov*[count]; //{ new Snov(), new Snov(std::string("zrak"), 1.0, 1.2922, Snov::PLIN), new Snov("kovina", 2, 7870, Snov::TRDA_SNOV), new Snov(*snovi[1]), new Snov("iridij", 100, 22400, Snov::TRDA_SNOV) };
	snovi[0] = new Snov();
	snovi[1] = new Snov(std::string("zrak"), 1.0, 1.2922, Snov::PLIN),
	snovi[2] = new Snov("kovina", 200, 7870, Snov::TRDA_SNOV);
	snovi[3] = new Snov(*snovi[1]);
	snovi[4] = new Snov("iridij", 1000, 22400, Snov::TRDA_SNOV);

	snovi[3]->setIme("helij");
	snovi[3]->setGostota(0.164);


	cout << steviloTezjihOdVode(snovi, count) << " snovi je tezjih od vode" << endl;
	cout << snovi[2]->getIme() << (snovi[1]->gostejsa(snovi[2]) ? " je" : " ni") << " gostejsa od " << snovi[1]->getIme() << endl;
	cout << "najgostejsa snov je " << Snov::Najgostejsa(snovi, count)->getIme() << endl;

	cout << "snovi med 500 in 800 kg/m^3:" << endl;
	for (int i = 0; i < 5; i++)
	{
		if (snovi[i]->getGostota() > 500 && snovi[i]->getGostota() < 800)
			cout << snovi[i]->toString() << endl;
	}

	cout << endl << "snovi trdega stanja:" << endl;
	for (int i = 0; i < 5; i++)
	{
		if (snovi[i]->getTip() == Snov::TRDA_SNOV)
			cout << snovi[i]->toString() << endl;
	}

	for (size_t i = 0; i < count; i++)
	{
		delete snovi[i];
	}
	delete[] snovi;


	system("pause");
}