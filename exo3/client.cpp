#include "Repas.h"

Choix::Items menu;

std::ostream& operator<<(std::ostream& os, const Repas& repas)
{
    std::ostringstream oss;
    cereal::BinaryOutputArchive oarchive(oss);
    oarchive(repas);
    std::string str = oss.str();
    return os << base64_encode((const unsigned char *)str.c_str(), str.length()) << std::endl;
}

void commander(const Repas& repas) { std::cout << repas; }

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