#ifndef UTILS_KEYWORDS_H
#define UTILS_KEYWORDS_H

#include <functional> // std::function
#include <iostream> // std::cerr
#include <vector> // std::vector

#define unless(condition) if(!(condition))
#define until(condition) while(!(condition))

#define require assert
#define ensure assert

#define assert(condition, message) \
    if (!(condition)) { \
        std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                << " line " << __LINE__ << ": " << message << std::endl; \
        std::terminate(); \
    }

template <typename T>
std::function<bool(T)> in(T min, T max) {
    return [min,max](T n) {
        if (n < min) return false;
        if (n > max) return false;
        return true;
    };
}

std::vector<int> range(int from, int to) {
    std::vector<int> res;
    for (int i = from; i <= to; ++i) {
        res.push_back(i);
    }
    return res;
}

#endif
