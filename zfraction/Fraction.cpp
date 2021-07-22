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

std::ostream& operator<<(std::ostream& os, const Fraction& frac)
{
    return os << frac.numerateur << "/" << frac.denominateur;
}

bool operator>(const Fraction& lhs, const Fraction& rhs)
{
    return (lhs.numerateur/lhs.denominateur)
         > (rhs.numerateur/rhs.denominateur);
}

bool operator==(const Fraction& lhs, const Fraction& rhs)
{
    return (lhs.numerateur == rhs.denominateur)
        && (rhs.numerateur == rhs.denominateur);
}

Fraction operator+(const Fraction& lhs, const Fraction& rhs)
{
    Fraction copie(lhs);
    return Fraction(copie += rhs); // on appelle le constructeur pour simplifier
}

Fraction operator*(const Fraction& lhs, const Fraction& rhs)
{
    Fraction copie(lhs);
    return Fraction(copie *= rhs); // on appelle le constructeur pour simplifier
}
