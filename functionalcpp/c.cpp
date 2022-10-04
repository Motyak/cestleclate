#include <vector>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <cmath>

template<class T> using Set = std::vector<T>;
using Duration = float;
using Estimation = Duration;
using ErrorMargin = Duration;

Estimation calculate_raw_estimation(Set<Duration> history) {
    Duration sum = std::accumulate(history.begin(), history.end(), 0.0f);
    return sum / history.size();
}

ErrorMargin calculate_margin_error(Set<Duration> history, Estimation raw_estimation) {
    Duration min = *std::min_element(history.begin(), history.end());
    Duration max = *std::max_element(history.begin(), history.end());
    return (max - min) / 2.0;
}

Estimation calculate_adjusted_estimation(Estimation raw_estimation, ErrorMargin error_margin) {
    return std::ceil(raw_estimation + error_margin);
}

using RawEstimationFunction = std::function<Estimation(Set<Duration>)>;
using ErrorMarginFunction = std::function<ErrorMargin(Set<Duration>, Estimation)>;
using AdjustedEstimationFunction = std::function<Estimation(Estimation, ErrorMargin)>;
using Estimator = std::function<Estimation(Set<Duration>)>;

Estimator create_estimator(RawEstimationFunction fnA, ErrorMarginFunction fnB, AdjustedEstimationFunction fnC) {
    return [fnA, fnB, fnC](Set<Duration> history) {
        Estimation raw_estimation = fnA(history);
        ErrorMargin error_margin = fnB(history, raw_estimation);
        Estimation adjusted_estimation = fnC(raw_estimation, error_margin);
        return adjusted_estimation;
    };
}

int main()
{
    auto history = Set<Duration>{2, 5, 7, 1};
    Estimator estimator = create_estimator(
        calculate_raw_estimation,
        calculate_margin_error,
        calculate_adjusted_estimation
    );
    std::cout << estimator(history) << std::endl;
}

