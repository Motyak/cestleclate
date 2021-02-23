#include "Repas.h"

void Repas::evoluer()
{
    std::visit(Evolution {
        [](const Budget& budget) {
            // générer choix pour maximisation calories
            // sans dépasser le budget
            // *this = ...
            // this->evoluer();
        },
        [](const Choix::Items& items) {
            // création de la commande (prix des items + prix total)
            // *this = ...
            // this->evoluer();
        },
        [](auto commande) {}
    }, this->forme);
}