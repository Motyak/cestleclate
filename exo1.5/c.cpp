#!/bin/transpiler
#include "includes.h" // iostream, ctime, cstring, chrono, thread

using Temps = std::time_t;
using Duree = std::chrono::duration<double>;

void attendre(const Duree& d) { std::this_thread::sleep_for(d); }

class Horloge
{
    Temps t;

    void actualiser() { std::time(&this->t); }
    void actualiserPeriodiquement()
    {
        while(true)
        {
            this->actualiser();
            attendre(1s);
        }
    }

  public: 
    Horloge()
    {
        std::thread(&Horloge::actualiserPeriodiquement, this)
                   .detach();
    }
    friend std::ostream& operator<<(std::ostream& os, const Horloge& h)
    {
        char* heure = std::ctime(&h.t);
        heure[strlen(heure) - 1] = '\0';
        return os << heure;
    }
} heure;

void afficher(const Horloge& h) { std::cout << h << std::endl; }

int main()
{
    afficher(heure);
    attendre(3s);
    afficher(heure);
}