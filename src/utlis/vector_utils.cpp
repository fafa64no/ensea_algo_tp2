//
// Created by sebas on 10/22/25.
//

#include "vector_utils.h"

#include <numeric>
#include <ranges>


int get_vector_sum(std::vector<int> data) {
    return std::accumulate(data.begin(), data.end(), 0);
}

int get_vector_sum(std::vector<std::pair<int, int>> data) {
    int sum = 0;
    for (const auto val : data | std::views::values) {
        sum += val;
    }
    return sum;
}











