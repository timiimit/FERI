#include <iostream>
#include "Tocka.h"
#include <cmath>

using namespace std;


Tocka::Tocka() : x(0), y(0) {
}

Tocka::Tocka(const Tocka& t) : x(t.x),  y(t.y) {
}

Tocka::Tocka(int xy) : x(xy), y(xy) {
}

Tocka::Tocka (int x1, int y1) : x(x1), y(y1) {
}


Tocka::~Tocka() {
}


int Tocka::getX() const {
  return x;
}

int Tocka::getY() const {
  return y;
}

void Tocka::print() const {
  cout << "(" << x << ", " << y << ")";
}


double Tocka::razdalja(Tocka t) const {
   //return sqrt((double)(this->x-t.x)*(x-t.x)+(y-t.y)*(y-t.y));
   return sqrt((double)(x - t.x)*(x - t.x)+(y - t.y)*(y - t.y));
}

Tocka Tocka::vrniZrcalnoTockoX() const
{
	return Tocka(-x, y);
}
