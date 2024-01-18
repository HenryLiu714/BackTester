#include "performance.h"

#include <cmath>

double arithmetic_mean(const std::vector<double>& nums) {
    double total = 0;
    for (double d : nums) total += d;
    return total / nums.size();
}

double std_dev(const std::vector<double>& nums) {
    double avg = arithmetic_mean(nums);
    double sum = 0;
    for (const auto& d : nums) sum += (d - avg) * (d - avg);
    return std::sqrt(sum / nums.size());
}

double create_sharpe_ratio(const std::vector<double>& returns, int periods) {
    return std::sqrt(periods) * arithmetic_mean(returns) / std_dev(returns);
}