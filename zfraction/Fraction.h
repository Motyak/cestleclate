#ifndef FRACTION_H
#define FRACTION_H

#include <ostream> // std::ostream

class Fraction
{
    int numerateur, denominateur;

  public:
    Fraction(int = 0, int = 1);
    Fraction(const Fraction&);

    Fraction& operator+=(const Fraction&);
    Fraction& operator*=(const Fraction&);
    friend std::ostream& operator<<(std::ostream&, const Fraction&);
    friend bool operator>(const Fraction&, const Fraction&);
    friend bool operator==(const Fraction&, const Fraction&);
};
Fraction operator+(const Fraction&, const Fraction&);
Fraction operator*(const Fraction&, const Fraction&);

#endif

