#include "includes.h" //cereal

template<class... Ts> struct Evolution : Ts... { using Ts::operator()...; };
template<class... Ts> Evolution(Ts...) -> Evolution<Ts...>;

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

using Forme = std::variant<Budget,Choix::Items,Commande>;
struct Repas 
{
    Forme forme;

    Repas(Forme forme) : forme(forme) { this->evoluer(); }
    template<class Archive> void serialize(Archive& ar) { ar(forme); }
    void evoluer();
};