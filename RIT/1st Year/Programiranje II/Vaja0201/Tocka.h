#ifndef TOCKA_H_
#define TOCKA_H_

class Tocka {
  private:
    int x, y;
  public:
    // privzeti konstruktor
    Tocka();
    // kopirni konstruktor
    Tocka(const Tocka& t);
    // pretvorbeni konstruktor
    Tocka(int xy);
    // konstruktor
    Tocka (int x1, int y1);
    // destruktor
    ~Tocka();
    // metode
    int getX() const;
    int getY() const;
    void print() const;
    double razdalja(Tocka t) const;
	Tocka vrniZrcalnoTockoX() const;

};

#endif /* TOCKA_H_ */
