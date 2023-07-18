#include "gtest/gtest.h"

#include "../simple_moving_average/simple_moving_average.h"
#include "../utils/utils.h"

#include <algorithm>
#include <random>
#include <vector>

namespace {
    template<typename T>
    bool CompareFloatVectors(const std::vector<T> &lhs, const std::vector<T> &rhs) {
        const T eps = 0.0001;

        if (lhs.size() != rhs.size()) {
            return false;
        }

        bool is_equal = true;
        for (size_t i = 0; i < lhs.size(); ++i) {
            is_equal &= std::fabs(lhs[i] - rhs[i]) < eps;
        }

        return is_equal;
    }

    template<typename T>
    T GetArrayAverage(const std::vector<T> &array) {
        return std::accumulate(array.begin(), array.end(), 0.0) / array.size();
    }
}

TEST(simple_moving_average_params, incorrect_moving_window_size) {
    const auto function_mock = utils::GenerateRandomArray<double>(10);
    int moving_window_size = -1;

    EXPECT_THROW(moving_averages::CalculateSimpleMovingAverage(function_mock, moving_window_size), std::logic_error);
}

TEST(simple_moving_average_params, incorrect_moving_window_size_too_large) {
    const auto function_mock = utils::GenerateRandomArray<float>(5);
    const int moving_window_size = 10;

    EXPECT_THROW(moving_averages::CalculateSimpleMovingAverage(function_mock, moving_window_size), std::logic_error);
}

TEST(simple_moving_average_algorithm, static_tests_double) {
    const std::vector<double> function_mock = {4.2, 2.7, 3.6, 5.4, 6.0};
    const int moving_window_size = 3;

    auto result = moving_averages::CalculateSimpleMovingAverage(function_mock, moving_window_size);
    const std::vector<double> expected_result = {3.5, 3.9, 5};

    EXPECT_PRED2(CompareFloatVectors<double>, result, expected_result);
}

TEST(simple_moving_average_algorithm, generated_test_double) {
    const int moving_window_size = 3;
    const int chunks_count = 10;
    const auto function_mock = utils::GenerateRepeatedChunksArray<double>(chunks_count, moving_window_size);

    auto result = moving_averages::CalculateSimpleMovingAverage(function_mock, moving_window_size);
    const std::vector<double> expected_result(moving_window_size * (chunks_count - 1) + 1,
                                              GetArrayAverage(function_mock));

    EXPECT_PRED2(CompareFloatVectors<double>, result, expected_result);
}

TEST(simple_moving_average_algorithm, static_tests_float) {
    const std::vector<float> function_mock = {4.2, 2.7, 3.6, 5.4, 6.0};
    const int moving_window_size = 3;

    auto result = moving_averages::CalculateSimpleMovingAverage(function_mock, moving_window_size);
    const std::vector<float> expected_result = {3.5, 3.9, 5};

    EXPECT_PRED2(CompareFloatVectors<float>, result, expected_result);
}

TEST(simple_moving_average_algorithm, generated_test_float) {
    const int moving_window_size = 3;
    const int chunks_count = 10;
    const auto function_mock = utils::GenerateRepeatedChunksArray<float>(chunks_count, moving_window_size);

    auto result = moving_averages::CalculateSimpleMovingAverage(function_mock, moving_window_size);
    const std::vector<float> expected_result(moving_window_size * (chunks_count - 1) + 1,
                                             GetArrayAverage(function_mock));

    EXPECT_PRED2(CompareFloatVectors<float>, result, expected_result);
}
