#include <iostream>

enum Couleur
{
    AUCUNE,
    BLEUE, VERTE, NOIRE, ROUGE
};

const char *ansicode[] = {
    "", 
    "\u001b[34m", "\u001b[32m", "\u001b[30m", "\u001b[31m"
};

class StyloQuatreCouleurs
{
    Couleur stylo = AUCUNE;
    
  public:
  
    StyloQuatreCouleurs()
    {
        std::cout << "\u001b[47m";
    }
    
    ~StyloQuatreCouleurs()
    {
        std::cout << "\u001b[0m" << std::endl;
    }

    StyloQuatreCouleurs* ecrire(const char* mots)
    {
        std::cout << ansicode[this->stylo] << mots;
        return this;
    }
    
    StyloQuatreCouleurs* changer(Couleur stylo)
    {
        this->stylo = stylo;
        return this;
    }
} stylo;

int main()
{
    stylo.ecrire("Je")
      -> changer(Couleur::BLEUE)
        -> ecrire("Je peux écrire en bleu,")
          -> changer(Couleur::VERTE)
            -> ecrire("en vert, ")
              -> changer(Couleur::NOIRE)
                -> ecrire("en noir ")
                  -> changer(Couleur::ROUGE)
                    -> ecrire("et en rouge !");
}
