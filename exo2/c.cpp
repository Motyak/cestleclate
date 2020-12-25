#include <iostream>
#include <cwchar>
#include <iomanip>

struct Prix
{
    wchar_t devise;
    double valeur;
};

Prix prix;

using Pourcentage = double;

Prix operator-(const Prix& pr, const Pourcentage& po)
{
    return {pr.devise, pr.valeur - pr.valeur * (po / 100)};
}

std::wostream& operator<<(std::wostream& os, const Prix& p)
{
    if(p.devise == '$')
        return os << p.devise << p.valeur;
    return os << p.valeur << p.devise;
}

void afficher(const Prix& p) 
{ 
    std::wcout << std::setprecision(2) << std::fixed << p 
            << std::endl; 
}

int main()
{
    prix = Prix{'$', 99.99} - Pourcentage{25};
    afficher(prix);
}