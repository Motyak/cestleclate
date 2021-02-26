#include "Repas.h"

Repas repas;

std::istream& operator>>(std::istream& is, Repas& repas)
{
    cereal::BinaryInputArchive iarchive(is);
    iarchive(repas);
    return is;
}

void preparer(Repas& repas) { std::cin >> repas; }

void afficher(Repas& repas)
{
    std::visit(overload{
        [&](const Budget& budget) {
            std::wcout<<budget.valeur<<budget.devise<<std::endl;
        },
        [&](const Choix::Items& items) {
            struct{Prix prix={L'€',0.0}; Calories cal=0;} total;
            std::wstring commande;
            for (const auto& [item, quantite] : items)
            {
                total.prix.valeur += Choix::prix[item].valeur * quantite;
                total.cal += Choix::cal[item] * quantite;
                commande += Choix::str[item] + L": " + std::to_wstring(quantite) + L"x\n";
            }
            commande += L"Total: " + std::to_wstring(total.prix.valeur) + L"€ " + std::to_wstring(total.cal) + L"Cal." ;
            afficher(repas = commande);
        },
        [](auto commande){ std::wcout << commande << std::endl; }
    }, repas);
}

int main()
{
    preparer(repas);
    afficher(repas);

    preparer(repas);
    afficher(repas);
}