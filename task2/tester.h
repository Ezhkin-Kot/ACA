#pragma once
#include <chrono>
#include <functional>
#include <random>
#include <vector>

double MeasureSortTime(void (*const sort)(std::vector<int> &), std::size_t size,
                       int tests_count = 1, int minValue = 0,
                       int maxValue = 100000);
