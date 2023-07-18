#pragma once

#include <exception>
#include <vector>

namespace {
    template<typename T>
    void ValidateParams(const std::vector<T> &function, int moving_window_size) {
        if (moving_window_size <= 1) {
            throw std::logic_error("error");
        }

        if (moving_window_size >= function.size()) {
            throw std::logic_error("error");
        }
    }

    template<typename T>
    T GetFirstAverage(const std::vector<T> &function, int moving_window_size) {
        T window_sum = 0.0;
        for (size_t i = 0; i <= moving_window_size - 1; ++i) {
            window_sum += function[i];
        }

        return window_sum / moving_window_size;
    }
}

namespace moving_averages {

    template<typename T>
    std::vector<T> CalculateSimpleMovingAverage(const std::vector<T> &function, int moving_window_size) {
        ValidateParams(function, moving_window_size);

        std::vector<T> simple_moving_average;
        simple_moving_average.reserve(function.size() - moving_window_size);

        T current_average = GetFirstAverage(function, moving_window_size);
        simple_moving_average.push_back(current_average);

        for (size_t i = moving_window_size; i < function.size(); ++i) {
            current_average += -function[i - moving_window_size] + function[i];
            simple_moving_average.push_back(current_average);
        }

        return simple_moving_average;
    }

} // namespace moving_averages
