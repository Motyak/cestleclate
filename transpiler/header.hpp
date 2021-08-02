/* DEBUT DEFINITIONS TRANSPILER */
#include <iostream>
#include <cwchar>
#include <iomanip>

/* 'void' type replacement */
struct nada
{
    operator void() const {}
    operator bool() const { return true; }
};

struct Prix
{
    wchar_t devise;
    double valeur;
} prix;

using Pourcentage = double;

Prix operator-(const Prix& pr, const Pourcentage& po) {
    return {pr.devise, pr.valeur - pr.valeur * (po / 100)};
}

std::wostream& operator<<(std::wostream& os, const Prix& p)
{
    return p.devise == '$'? os << p.devise << p.valeur:
                            os << p.valeur << p.devise;
}

void afficher(const Prix& p) {
    std::wcout << std::setprecision(2) << std::fixed << p
               << std::endl;
}
/* FIN DEFINITIONS TRANSPILER */
