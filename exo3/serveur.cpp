#include "Repas.h"

Repas repas;
std::ifstream in("stdout", std::ifstream::binary);

std::istream& operator>>(std::istream& is, Repas& repas)
{
    cereal::BinaryInputArchive iarchive(is);
    iarchive(repas);
    return is;
}

void preparer(Repas& repas) { in >> repas; }

void afficher(const Repas& repas) 
{
    std::visit(Evolution{
        [](const Budget& budget){std::wcout<<budget.valeur<<budget.devise<<std::endl;},
        [](const Choix::Items& items){
            for (auto& [key, value]: items)
                std::cout << key << " : " << value << std::endl;
        },
        [](auto autre){}
    }, repas.forme);
    // std::cout << std::get<Commande>(repas.forme) << std::endl;
}

int main()
{
    preparer(repas);
    afficher(repas);

    preparer(repas);
    afficher(repas);
}