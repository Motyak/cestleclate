#include "includes.h" //cereal

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;

using Calories = int;
using Quantite = int;
using Commande = std::string;

struct Prix
{
    wchar_t devise;
    double valeur;

    template<class Archive>
    void serialize(Archive& ar) { ar(devise, valeur); }
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

using Repas = std::variant<Budget,Choix::Items,Commande>;