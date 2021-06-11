#include "cereal/archives/binary.hpp"
#include "cereal/types/variant.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/map.hpp"
#include <iomanip>

/* overload pattern for in-place visitation using lambdas */
template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;

using Calories = int;
using Commande = std::wstring;

struct Prix
{
    wchar_t devise;
    double valeur;

    template<class Archive>
    void serialize(Archive& ar) { ar(devise, valeur); }
};
using Budget = Prix;

enum Item
{
    HAMBURGER = 1, WINGS = 2, FRITES = 4, NUGGETS = 8, 
    COCA = 16, SUNDAE = 32, BONBON = 64
};
using Items = unsigned char;

enum Menu
{
    LA_CLASSIQUE = HAMBURGER | NUGGETS | COCA, 
    LE_GOURMAND = WINGS | FRITES | COCA | SUNDAE,
    LE_PAUVRE = BONBON
};

struct Info { const char* nom; Calories cal; Prix prix; };
std::map<Item,Info> info {
    {HAMBURGER, Info{"Hamburger", 220Cal., 1.90€}},
    {WINGS, Info{"Wings", 300Cal., 2.10€}},
    {FRITES, Info{"Frites", 320Cal., 2.50€}},
    {NUGGETS, Info{"Nuggets", 310Cal., 2.70€}},
    {COCA, Info{"Coca-cola", 100Cal., 2.00€}},
    {SUNDAE, Info{"Sundae", 300Cal., 3.00€}},
    {BONBON, Info{"Bonbon", 1Cal., 0.00€}},
};

using Repas = std::variant<Budget,Items,Commande>;