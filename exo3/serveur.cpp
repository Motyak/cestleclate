#include "Repas.h"

Repas repas;

std::istream& operator>>(std::istream& is, Repas& repas)
{
    cereal::BinaryInputArchive iarchive(is);
    iarchive(repas);
    return is;
}

void preparer(Repas& repas) { std::cin >> repas; }

void afficher(const Repas& repas)
{
    std::visit(overload{
        [](const Budget& budget){std::wcout<<budget.valeur<<budget.devise<<std::endl;},
        [](const Choix::Items& items){
            for (auto& [key, value]: items)
                std::wcout << key << " : " << value << std::endl;
        },
        [](auto autre){}
    }, repas);
}

int main()
{
    preparer(repas);
    afficher(repas);

    preparer(repas);
    afficher(repas);
}