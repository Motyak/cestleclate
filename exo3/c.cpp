#!/bin/transpiler
#include "Repas.h"

#ifdef client
    std::ostream& operator<<(std::ostream& os, const Repas& repas)
    {
        (cereal::BinaryOutputArchive(os))(repas);
        return os;
    }

    void commander(const Repas& repas) { std::cout << repas; }

    int main()
    {
        commander(Repas{7.00€});

        commander(Repas{Menu::LE_GOURMAND});

        commander(Repas{HAMBURGER | FRITES | COCA});

        commander(Repas{});
    }
#endif

#ifdef serveur
    Repas repas;

    std::istream& operator>>(std::istream& is, Repas& repas)
    {
        (cereal::BinaryInputArchive(is))(repas);
        return is;
    }

    void prendreConnaissance(Repas& repas) { std::cin >> repas; }

    void presenter(Repas& repas)
    {
        std::visit(overload{
            [&](const Budget& budget)
            {
                if(budget.valeur >= 9.60)
                    presenter(repas = Menu::LE_GOURMAND);
                else if(budget.valeur >= 6.60)
                    presenter(repas = Menu::LA_CLASSIQUE);
                else /* pas assez d'argent */
                    presenter(repas = Menu::LE_PAUVRE);
            },
            [&](const Items& items)
            {
                struct{Prix prix={L'€',0.0}; Calories cal=0;} total;
                std::wostringstream commande;
                commande.precision(2);
                commande.setf(std::ios::fixed);
                
                for(int i = (1 << 0); i < (1 << 8); (i <<= 1))
                {
                    if((items & i) == i)
                    {
                        const Item& item = static_cast<Item>(i);
                        total.prix.valeur += info.at(item).prix.valeur;
                        total.cal += info.at(item).cal;
                        commande << info.at(item).nom << ": x1" << std::endl;
                    }
                }
                commande << "Total: " << total.prix.valeur << total.prix.devise;
                commande << ' ' << total.cal << "Cal." << std::endl;

                presenter(repas = commande.str());
            },
            [](auto commande){ std::wcout << commande << std::endl; }
        }, repas);
    }

    int main()
    {
        prendreConnaissance(repas);
        presenter(repas);

        prendreConnaissance(repas);
        presenter(repas);

        prendreConnaissance(repas);
        presenter(repas);

        prendreConnaissance(repas);
        presenter(repas);
    }
#endif
