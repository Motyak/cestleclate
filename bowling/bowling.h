#ifndef BOWLING_H
#define BOWLING_H

#include <vector>
#include <variant>

namespace bowling
{
    const int NB_QUILLES_MAX = 10;

    using Tours = std::initializer_list<std::vector<int>>;

    using LancerUnique = int;
    using DeuxLancers = std::pair<int,int>;
    using Tour = std::variant<LancerUnique,DeuxLancers>;
};

#endif
