#include <iostream>

enum Jour
{
    lundi, mardi, mercredi, jeudi, vendredi,
    samedi, dimanche
};

Jour jour;

std::string str[] 
{ 
    "lundi", "mardi", "mercredi", "jeudi", "vendredi",
    "samedi", "dimanche" 
};

Jour operator+(const Jour& j, const int i)
{
    return (Jour)(((int)j + i) % 7);
}

std::ostream& operator<<(std::ostream& os, const Jour& j)
{
    os << str[j];
    return os;
}

void print(const Jour& j) { std::cout << j << std::endl; }

int main()
{
    jour = mardi + 6;
    print(jour);
}
