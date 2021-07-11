#include <iostream>
#include <ctime>
#include <cstring>
#include <chrono>
#include <thread>

using Temps = std::time_t;
using Duree = std::chrono::duration<double>;

void attendre(const Duree& d) { std::this_thread::sleep_for(d); }

class Horloge
{
    Temps t;

    void actualiser() { std::time(&this->t); }
    void actualiserPeriodiquement() {
        while(attendre(1s)) this->actualiser();
    }

  public:
    Horloge() : t(std::time(nullptr))
    {
        std::thread(&Horloge::actualiserPeriodiquement, this)
                   .detach();
    }
    friend std::ostream& operator<<(std::ostream& os, const Horloge& h)
    {
        return os << std::strtok(std::ctime(&h.t), "\n");
    }
} heure;

void afficher(const Horloge& h) { std::cout << h << std::endl; }

int main()
{
    afficher(heure);
    attendre(3s);
    afficher(heure);
}
