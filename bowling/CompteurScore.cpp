#include "CompteurScore.h"

#include <numeric>

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


bowling::CompteurScore::CompteurScore(bowling::Tours tours)
{
    // fonction pour construire un type de tour et l'ajouter en début de partie
    auto ajouterTour = [this](std::unique_ptr<Tour>&& tour){partie.insert(partie.begin(), std::move(tour));};

    std::shared_ptr<LancerUnique> lancerSuccesseur = AUCUN_SUCCESSEUR;
    std::shared_ptr<LancerUnique> lancerSuccesseurSuccesseur = AUCUN_SUCCESSEUR;

    for (auto it = std::rbegin(tours); it != std::rend(tours); ++it)
    {
        auto tourActuel = ((*it).size() == 1)? bowling::Tour((*it)[0]) : bowling::Tour(std::pair{(*it)[0], (*it)[1]});

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
    return std::accumulate(
        this->partie.cbegin(),
        this->partie.cend(),
        0,
        [](int i, auto& t) { return i + (*t).compterScore(); }
    );
}
