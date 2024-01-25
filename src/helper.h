#ifndef HELPER_H
#define HELPER_H

#include <vector>
/**
 * Finds the arithmetic mean of vector of numbers
 * @param  nums      : The numbers
 * @return {double}  : The mean
 */
double arithmetic_mean(const std::vector<double>& nums);

/**
 * Finds the standard deviation of numbers 
 * @param  nums      : The numbers
 * @return {double}  : The standard deviation
 */
double std_dev(const std::vector<double>& nums);

#endif