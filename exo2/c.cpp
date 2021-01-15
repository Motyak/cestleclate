#!/bin/transpiler
#include <iostream>
#include <cwchar>
#include <iomanip>

struct Prix
{
    wchar_t devise;
    double valeur;
} prix;

using Pourcentage = double;

Prix operator-(const Prix& pr, const Pourcentage& po)
{
    return {pr.devise, pr.valeur - pr.valeur * (po / 100)};
}

std::wostream& operator<<(std::wostream& os, const Prix& p)
{
    return p.devise == '$'? os << p.devise << p.valeur:
                            os << p.valeur << p.devise;
}

void afficher(const Prix& p)
{
    std::wcout << std::setprecision(2) << std::fixed << p
               << std::endl;
}

int main()
{
    prix = 91€ - 13.37%;
    afficher(prix);
}
