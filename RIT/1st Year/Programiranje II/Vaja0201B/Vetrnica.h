#pragma once
#include <string>

class Vetrnica
{
private:
	int stKrakov;
	float sirinaKrakov;
	float dolzinaKrakov;
	std::string lastnik;

public:
	Vetrnica();
	Vetrnica(const Vetrnica& c);
	~Vetrnica();

	int getSteviloKrakov() const;
	void setSteviloKrakov(int nStKrakov);

	float getSirinaKrakov() const;
	void setSirinaKrakov(float nSirinaKrakov);

	float getDolzinaKrakov() const;
	void setDolzinaKrakov(float nDolzinaKrakov);

	std::string getLastnik() const;
	void setLastnik(std::string owner);

	void izpis() const;
	std::string toString() const;

	void read();
};