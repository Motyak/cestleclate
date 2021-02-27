#include "Repas.h"

Repas repas;

std::istream& operator>>(std::istream& is, Repas& repas)
{
    cereal::BinaryInputArchive iarchive(is);
    iarchive(repas);
    return is;
}

void preparer(Repas& repas) { std::cin >> repas; }

void presenter(Repas& repas)
{
    std::visit(overload{
        [&](const Budget& budget) {
            std::wcout << std::setprecision(2) << std::fixed << budget.valeur 
                       << budget.devise << std::endl;
        },
        [&](const Choix::Items& items) {
            const wchar_t devise = (*Choix::prix).devise;
            struct{Prix prix={devise,0.0}; Calories cal=0;} total;
            std::wostringstream commande;
            commande.precision(2);
            commande.setf(std::ios::fixed);
            for (const auto& [item, quantite] : items) {
                total.prix.valeur += Choix::prix[item].valeur * quantite;
                total.cal += Choix::cal[item] * quantite;
                commande << Choix::str[item] << ": " << quantite << "x\n";
            }
            commande << "Total: " << total.prix.valeur << devise << ' ' << total.cal << "Cal." ;
            presenter(repas = commande.str());
        },
        [](auto commande){ std::wcout << commande << std::endl; }
    }, repas);
}

int main()
{
    preparer(repas);
    presenter(repas);

    preparer(repas);
    presenter(repas);
}