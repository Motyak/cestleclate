#ifndef FRACTION_H
#define FRACTION_H

#include <ostream> // std::ostream

enum ResultatComparaison {
    PLUS_PETIT,
    EGAL,
    PLUS_GRAND 
};

class Fraction
{
    int numerateur;
    int denominateur;

    bool estEgal(const Fraction&) const;

  public:
    Fraction(int = 0, int = 1);
    Fraction(const Fraction&);

    void ecrire(std::ostream&) const; 
    ResultatComparaison comparer(const Fraction&) const;
    Fraction& operator+=(const Fraction&);
    Fraction& operator*=(const Fraction&);
};

std::ostream& operator<<(std::ostream&, const Fraction&);
bool operator>(const Fraction&, const Fraction&);
bool operator==(const Fraction&, const Fraction&);
Fraction operator+(const Fraction&, const Fraction&);
Fraction operator*(const Fraction&, const Fraction&);

#endif

