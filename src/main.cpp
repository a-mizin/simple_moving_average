#include "simple_moving_average/simple_moving_average.h"
#include "utils/utils.h"

#include <chrono>
#include <vector>
#include <iostream>
#include <tuple>

namespace {
    const double kMillisecondsFactor = 1000.0;

    const int kTriesCount = 10;

    const int kFunctionSize = 1'048'576;
    const std::vector<int> kMovingWindowSizes = {4, 8, 16, 32, 64, 128};

    std::chrono::milliseconds
    GetAverageExecutingTime(const std::vector<double> &function, const int moving_window_size) {
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < kTriesCount; ++i) {
            std::ignore = moving_averages::CalculateSimpleMovingAverage(function, moving_window_size);
        };
        auto end = std::chrono::steady_clock::now();

        return duration_cast<std::chrono::milliseconds>(end - start) / kTriesCount;
    }

    void RunTests() {
        for (const auto &moving_window_size: kMovingWindowSizes) {
            const auto function = utils::GenerateRepeatedChunksArray<double>(kFunctionSize / moving_window_size,
                                                                             moving_window_size);
            const auto average_executing_time = GetAverageExecutingTime(function, moving_window_size);
            std::cout << "Moving window size: " << moving_window_size << "\n"
                      << "Average executing time: " << average_executing_time.count() / kMillisecondsFactor
                      << "s. \n\n";
        }
    }
}

int main() {
    RunTests();

    return 0;
}
