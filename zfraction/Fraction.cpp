#include "Fraction.h"

#include <numeric> // std::gcd

Fraction::Fraction(int num, int denom)
{
    /* on s'assure que la fraction soit simplifiée */
    const int gcd = std::gcd(denom, num);
    this->numerateur = (int)num / gcd;
    this->denominateur = (int)denom / gcd;

    /* on retire les signes négatifs inutiles */
    if(this->numerateur < 0 && this->denominateur < 0)
    {
        this->numerateur = -this->numerateur;
        this->denominateur = -this->denominateur;
    }
}

Fraction::Fraction(const Fraction& other)
        : Fraction(other.numerateur, other.denominateur){}

Fraction& Fraction::operator+=(const Fraction& rhs)
{
    //     a       c
    //    ---  +  ---
    //     b       d
    const int& a(this->numerateur), b(this->denominateur),
                    c(rhs.numerateur), d(rhs.denominateur);


    if(b == d)
        *this = {a + c, b + d};
    /* else -- denominateurs différents */

    const int denominateur = b * d;
    const int numerateur = a * d + c * b;

    *this = {numerateur, denominateur};
}

Fraction& Fraction::operator*=(const Fraction& rhs)
{
    //     a       c
    //    ---  x  ---
    //     b       d
    const int& a(this->numerateur), b(this->denominateur),
                    c(rhs.numerateur), d(rhs.denominateur);

    *this = {a * c, b * d};
}


void Fraction::ecrire(std::ostream& os) const {
    os << this->numerateur << "/" << this->denominateur;
}

std::ostream& operator<<(std::ostream& os, const Fraction& frac)
{
    frac.ecrire(os);
    return os;
}

bool Fraction::estEgal(const Fraction& other) const {
    return this->numerateur == other.denominateur
        && this->denominateur == other.denominateur; 
}

ResultatComparaison Fraction::comparer(const Fraction& rhs) const {
    float lhs_numeric = this->numerateur / this->denominateur;
    float rhs_numeric = rhs.numerateur / rhs.denominateur;

    if(this->estEgal(rhs)) {
        return ResultatComparaison::EGAL;
    } else if(lhs_numeric > rhs_numeric) {
        return ResultatComparaison::PLUS_GRAND;
    } else {
        return ResultatComparaison::PLUS_PETIT;
    }
}

bool operator>(const Fraction& lhs, const Fraction& rhs)
{
    return lhs.comparer(rhs) == ResultatComparaison::PLUS_GRAND; 
}

bool operator==(const Fraction& lhs, const Fraction& rhs)
{
    return lhs.comparer(rhs) == ResultatComparaison::EGAL; 
}

Fraction operator+(const Fraction& lhs, const Fraction& rhs)
{
    Fraction copie(lhs);
    // on appelle le constructeur pour simplifier
    return Fraction(copie += rhs);
}

Fraction operator*(const Fraction& lhs, const Fraction& rhs)
{
    Fraction copie(lhs);
    // on appelle le constructeur pour simplifier
    return Fraction(copie *= rhs);
}
