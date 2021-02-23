#include "Repas.h"

Choix::Items menu;
std::ofstream out("stdout", std::ofstream::binary | std::ofstream::trunc);

std::ostream& operator<<(std::ostream& os, const Repas& repas)
{
    std::ostringstream oss;

    // cereal::BinaryOutputArchive oarchive(os);
    cereal::BinaryOutputArchive oarchive(oss);
    oarchive(repas);
    return os << oss.str();
}

void commander(const Repas& repas) { out << repas; }
// void commander(const Repas& repas) { std::cout << repas; }

int main()
{
    // commander(Repas{$10.00});
    commander(Repas{Prix{L"€", 10.00}});

    // menu[Choix::Item::CHEESEBURGER] = 1x;
    // menu[Choix::Item::FRITES_MOYENNE] = 1x;
    menu[Choix::Item::CHEESEBURGER] = Quantite{1};
    menu[Choix::Item::FRITES_MOYENNE] = Quantite{1};
    commander(Repas{menu});
}