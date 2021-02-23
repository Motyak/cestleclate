#include "includes.h" // iostream, cwchar, map, variant

template<class... Ts> struct Evolution : Ts... { using Ts::operator()...; };
template<class... Ts> Evolution(Ts...) -> Evolution<Ts...>;

using Calories = int;
using Quantite = int;
using Commande = std::string;

struct Prix
{
    wchar_t devise;
    double valeur;
};
using Budget = Prix;

struct Choix
{
    enum Item {
        CHEESEBURGER,   DOUBLE_CHEESE,
        FRITES_MOYENNE, FRITES_GRANDE
    };
    using Items = std::map<Choix::Item,Quantite>;

    inline static const Calories cal[4]{220Cal., 440Cal., 320Cal., 490Cal.};
    inline static const Prix prix[4]{1.90€, 3.50€, 2.50€, 2.90€};
};
Choix::Items menu;

using Forme = std::variant<Budget,Choix::Items,Commande>;
struct Repas 
{
    Forme forme;

    Repas(Forme forme) : forme(forme) { this->evoluer(); }
    void evoluer()
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
};

std::ostream& operator<<(std::ostream& os, const Repas& repas)
{
    return os << std::get<Commande>(repas.forme);
}

void commander(const Repas& repas) {
    std::cout << "Commande : " << std::endl << repas
              << std::endl << std::endl;
}

int main()
{
    commander(Repas{10€});

    menu[Choix::Item::CHEESEBURGER] = 1x;
    menu[Choix::Item::FRITES_MOYENNE] = 1x;
    commander(Repas{menu});
}