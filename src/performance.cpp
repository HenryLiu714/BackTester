#include "performance.h"
#include "helper.h"

#include <cmath>

double create_sharpe_ratio(const std::vector<double>& returns, int periods) {
    return arithmetic_mean(returns) / std_dev(returns);
}