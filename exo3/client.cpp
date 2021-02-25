#include "Repas.h"

Choix::Items menu;

std::ostream& operator<<(std::ostream& os, const Repas& repas)
{
    cereal::BinaryOutputArchive oarchive(os);
    oarchive(repas);
    return os;
}

void commander(const Repas& repas) { std::cout << repas; }

int main()
{
    commander(Repas{10.00€});

    menu[Choix::Item::CHEESEBURGER] = 1x;
    menu[Choix::Item::FRITES_MOYENNE] = 1x;
    commander(Repas{menu});
}