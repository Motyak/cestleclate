#!/bin/transpiler
#include "Repas.h"

#ifdef client
    Choix::Items menu;

    std::ostream& operator<<(std::ostream& os, const Repas& repas)
    {
        (cereal::BinaryOutputArchive(os))(repas);
        return os;
    }

    void commander(const Repas& repas) { std::cout << repas; }

    int main()
    {
        commander(Repas{4.00€});

        menu[Choix::Item::CHEESEBURGER] = 1x;
        menu[Choix::Item::FRITES_MOYENNE] = 1x;
        commander(Repas{menu});
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
                Choix::Items items;

                if(budget.valeur >= 6.40)
                    items[Choix::Item::FRITES_GRANDE] = 1x;
                if(budget.valeur >= 3.50)
                    items[Choix::Item::DOUBLE_CHEESE] = 1x;
                else if(budget.valeur >= 1.90)
                    items[Choix::Item::CHEESEBURGER] = 1x;

                presenter(repas = items);
            },
            [&](const Choix::Items& items)
            {
                const wchar_t devise = (*Choix::prix).devise;
                struct{Prix prix={devise,0.0}; Calories cal=0;} total;
                std::wostringstream commande;
                commande.precision(2);
                commande.setf(std::ios::fixed);

                for (const auto& [item, quantite] : items)
                {
                    total.prix.valeur += Choix::prix[item].valeur * quantite;
                    total.cal += Choix::cal[item] * quantite;
                    commande << Choix::str[item] << ": " << quantite 
                             << "x" << std::endl;
                }
                commande << "Total: ";
                if(devise == '$')
                    commande << devise << total.prix.valeur ;
                else
                    commande << total.prix.valeur << devise;
                commande << ' ' << total.cal << "Cal." ;

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
    }
#endif