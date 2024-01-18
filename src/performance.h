#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <vector>

/**
 * Some functions to be used to measure the performace of a Portfolio 
*/

double create_sharpe_ratio(const std::vector<double>& returns, int periods = 252);

#endif