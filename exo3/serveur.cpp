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
            std::wcout << std::setprecision(2) << std::fixed << budget.valeur 
                       << budget.devise << std::endl;
        },
        [&](const Choix::Items& items) {
            struct{Prix prix={L'€',0.0}; Calories cal=0;} total;
            std::wostringstream commande;
            commande.precision(2);
            commande.setf(std::ios::fixed);
            for (const auto& [item, quantite] : items)
            {
                total.prix.valeur += Choix::prix[item].valeur * quantite;
                total.cal += Choix::cal[item] * quantite;
                commande << Choix::str[item] << L": " << quantite << L"x\n";
            }
            commande << L"Total: " << total.prix.valeur << L"€ " << total.cal << L"Cal." ;
            afficher(repas = commande.str());
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