#pragma once

#include <vector>
#include <random>

namespace utils {
    template<typename T>
    std::vector<T> GenerateRandomArray(const size_t size) {
        std::random_device rd{};
        std::mt19937 gen{rd()};
        std::normal_distribution<T> d{5, 2};

        std::vector<T> generated_vector;
        generated_vector.reserve(size);

        for (size_t i = 0; i < size; ++i) {
            generated_vector.push_back(d(gen));
        }

        return generated_vector;
    }

    template<typename T>
    std::vector<T> GenerateRepeatedChunksArray(const int chunks_count, const size_t chunk_size) {
        const auto chunk = GenerateRandomArray<T>(chunk_size);

        std::vector<T> generated_array;
        generated_array.reserve(chunks_count * chunk_size);

        for (int i = 0; i < chunks_count; ++i) {
            std::copy(chunk.begin(), chunk.end(),
                      std::back_inserter(generated_array));
        }

        return generated_array;
    }
}
