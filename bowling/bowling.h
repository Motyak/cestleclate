#ifndef BOWLING_H
#define BOWLING_H

#include <vector>
#include <variant>

namespace bowling
{
    const int NB_QUILLES_MAX = 10;
    const int NB_TOURS_MAX = 10;

    using LancerUnique = int;
    using DeuxLancers = std::pair<int,int>;
    using Tour = std::variant<LancerUnique,DeuxLancers>;
    using Partie = std::vector<Tour>;
};

#endif