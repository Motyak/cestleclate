#ifndef COMPTEUR_SCORE_H
#define COMPTEUR_SCORE_H

#include "bowling.h"

#include <memory>

/* overload pattern for in-place visitation using lambdas */
template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;

namespace bowling
{
    class CompteurScore
    {
        static const std::shared_ptr<LancerUnique> AUCUN_SUCCESSEUR;

        struct Tour { virtual int compterScore() const = 0; };
        
        struct TourSimple : public Tour
        {
            int score = bowling::SCORE_INITIAL;

            TourSimple(int score);
            int compterScore() const override;
        };

        struct TourSpare : public Tour
        {
            std::shared_ptr<LancerUnique> lancerSuccesseur;

            TourSpare(const std::shared_ptr<LancerUnique>& successeur);
            int compterScore() const override;
        };

        struct TourStrike : public TourSpare
        {
            std::shared_ptr<LancerUnique> lancerSuccesseurSuccesseur;

            TourStrike(const std::shared_ptr<LancerUnique>& successeur, const std::shared_ptr<LancerUnique>& successeurSuccesseur);
            int compterScore() const override;
        };

        using Partie = std::vector<std::unique_ptr<Tour>>;
        Partie partie;

      public:
        CompteurScore(const bowling::Partie&);
        int operator()() const;
    };
};

#endif