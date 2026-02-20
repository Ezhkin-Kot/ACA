#include "tester.h"
#include <chrono>
#include <random>
#include <vector>
std::mt19937 rnd(time(NULL));

int getRandom(int min, int max) { return rnd() % (max - min + 1) + min; }

double MeasureSortTime(void (*const sort)(std::vector<int> &), std::size_t size,
                       int tests_count, int minValue, int maxValue) {
    std::vector<int> data(size);
    std::vector<double> durations(tests_count);

    for (int i = 0; i < tests_count; i++) {
        for (auto &value : data) {
            value = getRandom(minValue, maxValue);
        }

        auto start = std::chrono::high_resolution_clock::now();

        sort(data);

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> duration = end - start;
        durations[i] = duration.count();
    }

    double result_duration = 0;
    for (int i = 0; i < durations.size(); i++) {
        result_duration += durations[i];
    }
    result_duration /= tests_count;

    return result_duration;
}
