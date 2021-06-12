#include "CompteurScore.h"

const std::shared_ptr<int> bowling::CompteurScore::AUCUN_SUCCESSEUR = std::make_shared<LancerUnique>(0);


bowling::CompteurScore::TourSimple::TourSimple(int score) : score(score){}
bowling::CompteurScore::TourSpare::TourSpare(const std::shared_ptr<LancerUnique>& s) : lancerSuccesseur(s){}
bowling::CompteurScore::TourStrike::TourStrike(const std::shared_ptr<LancerUnique>& s1, const std::shared_ptr<LancerUnique>& s2) : TourSpare(s1), lancerSuccesseurSuccesseur(s2){}

int bowling::CompteurScore::TourSimple::compterScore() const
{
    return this->score;
}

int bowling::CompteurScore::TourSpare::compterScore() const
{
    return bowling::NB_QUILLES_MAX + *lancerSuccesseur;
}

int bowling::CompteurScore::TourStrike::compterScore() const
{
    return TourSpare::compterScore() + *lancerSuccesseurSuccesseur;
}


bowling::CompteurScore::CompteurScore(const bowling::Partie& p)
{
    // fonction pour construire un type de tour et l'ajouter en début de partie
    auto ajouterTour = [this](std::unique_ptr<Tour>&& tour){partie.insert(partie.begin(), std::move(tour));};

    std::shared_ptr<LancerUnique> lancerSuccesseur = AUCUN_SUCCESSEUR;
    std::shared_ptr<LancerUnique> lancerSuccesseurSuccesseur = AUCUN_SUCCESSEUR;

    for(auto it = p.rbegin(); it != p.rend(); ++it)
    {
        const bowling::Tour& tourActuel = *it;

        std::visit(overload{
            [&](LancerUnique lancer)
            {
                if(lancer == bowling::NB_QUILLES_MAX)
                    ajouterTour(std::make_unique<TourStrike>(lancerSuccesseur, lancerSuccesseurSuccesseur));
                else /* coup bonus */
                    ajouterTour(std::make_unique<TourSimple>(lancer));
                    
                lancerSuccesseurSuccesseur = lancerSuccesseur;
                lancerSuccesseur = std::make_shared<LancerUnique>(lancer);
            },
            [&](const DeuxLancers& lancers)
            {
                if(lancers.first + lancers.second == bowling::NB_QUILLES_MAX)
                    ajouterTour(std::make_unique<TourSpare>(lancerSuccesseur));
                else
                    ajouterTour(std::make_unique<TourSimple>(lancers.first + lancers.second));

                lancerSuccesseur = std::make_shared<LancerUnique>(lancers.first);
                lancerSuccesseurSuccesseur = std::make_shared<LancerUnique>(lancers.second);
            }
        }, tourActuel);
    }
}

int bowling::CompteurScore::operator()() const
{
    int sum = 0;
    for(int i = 0; i < this->partie.size() && i < bowling::NB_TOURS_MAX; ++i)
        sum += this->partie[i]->compterScore();
        
    return sum;
}
