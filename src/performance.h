#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <vector>

/**
 * Some functions to be used to measure the performace of a Portfolio 
*/

/**
 * Finds the sharpe ratio of a given number of trades
 * @param  returns   : Total returns over the given number of periods
 * @param  periods   : The number of trading periods, default 252
 * @return {double}  : The sharpe ratio of the trades
 */
double create_sharpe_ratio(const std::vector<double>& returns, int periods = 252);

#endif