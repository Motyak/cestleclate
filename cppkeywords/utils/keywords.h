#ifndef UTILS_KEYWORDS_H
#define UTILS_KEYWORDS_H

#include <functional> // std::function
#include <iostream> // std::cerr
#include <vector> // std::vector

// if condition isn't met
#define unless(condition) if(!(condition))

// while condition isn't met
#define until(condition) while(!(condition))

// when something is required
#define require assert

// when something is required at the moment BUT could be subject to change in the future
#define likely assert // not sure if relevant

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
