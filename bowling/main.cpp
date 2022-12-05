#include "CompteurScore.h"

#include <iostream>

// g++ --std=c++17 -o bowling CompteurScore.cpp main.cpp
int main()
{
    bowling::CompteurScore compteur = {
        { 10 },
        { 4, 6 },
        { 7, 3 },
        { 10 },
        { 10 },
        { 0, 0 },
        { 0, 0 }, 
        { 3, 5 },
        { 6, 4 },
        { 10 },
        { 10 },
        { 9 },
    };

    std::cout << "Le score de la partie est de : "
              << compteur() << std::endl;
}