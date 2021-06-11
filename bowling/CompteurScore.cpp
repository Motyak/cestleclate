#include "CompteurScore.h"

const std::shared_ptr<int> bowling::CompteurScore::AUCUN_SUCCESSEUR = std::make_shared<LancerUnique>(0);


bowling::CompteurScore::TourSimple::TourSimple(const bowling::Tour& t) : tour(t){}
bowling::CompteurScore::TourSpare::TourSpare(const std::shared_ptr<LancerUnique>& s) : lancerSuccesseur(s){}
bowling::CompteurScore::TourStrike::TourStrike(const std::shared_ptr<LancerUnique>& s1, const std::shared_ptr<LancerUnique>& s2) : TourSpare(s1), lancerSuccesseurSuccesseur(s2){}

int bowling::CompteurScore::TourSimple::compterScore() const
{
    return std::visit(overload{
        // coup bonus
        [](LancerUnique lancer) -> int {return lancer;},
        [](DeuxLancers lancers) -> int {return lancers.first + lancers.second;}
    }, this->tour); 
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
    std::shared_ptr<LancerUnique> lancerSuccesseur = AUCUN_SUCCESSEUR;
    std::shared_ptr<LancerUnique> lancerSuccesseurSuccesseur = AUCUN_SUCCESSEUR;

    for(auto it = p.rbegin(); it != p.rend(); ++it)
    {
        const bowling::Tour& tourActuel = *it;

        std::visit(overload{
            [&](LancerUnique lancer)
            {
                if(lancer == bowling::NB_QUILLES_MAX)
                    this->partie.insert(this->partie.begin(), std::make_unique<TourStrike>(lancerSuccesseur, lancerSuccesseurSuccesseur));
                else /* coup bonus */
                    this->partie.insert(this->partie.begin(), std::make_unique<TourSimple>(lancer));
                    
                lancerSuccesseurSuccesseur = lancerSuccesseur;
                lancerSuccesseur = std::make_shared<LancerUnique>(lancer);
            },
            [&](DeuxLancers lancers)
            {
                if(lancers.first + lancers.second == bowling::NB_QUILLES_MAX)
                    this->partie.insert(this->partie.begin(), std::make_unique<TourSpare>(lancerSuccesseur));
                else
                    this->partie.insert(this->partie.begin(), std::make_unique<TourSimple>(lancers));

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
