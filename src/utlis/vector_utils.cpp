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


std::vector<std::pair<int, int>> get_sequence_as_pairs(std::vector<int> data) {
    std::vector<std::pair<int, int>> sequence;
    for (int i = 0; i < data.size(); ++i) {
        sequence.emplace_back(i, data.at(i));
    }
    return sequence;
}









