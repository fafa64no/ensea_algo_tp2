//
// Created by sebas on 10/22/25.
//

#include "subsequence_finder.h"

#include <iostream>
#include <list>
#include <ostream>

#include "vector_utils.h"


std::vector<std::pair<int, int>> get_biggest_mono_subsequence(const std::vector<int>& data) {
    if (data.empty()) {
        return {};
    }

    std::list<std::vector<std::pair<int, int>>> available_subsequences;
    std::vector<std::pair<int, int>> biggest_subsequence;
    int max_subsequence_size = 0;

    for (int i = 0; i < data.size(); i++) {
        bool has_max_increased{false};
        std::list<std::vector<std::pair<int, int>>> new_subsequences;;
        for (auto& subsequence : available_subsequences) {
            if (subsequence.back().second + 1 == data[i]) {
                std::pair element(i, data[i]);
                subsequence.emplace_back(element);

                if (subsequence.size() > max_subsequence_size) {
                    max_subsequence_size = static_cast<int>(subsequence.size());
                    biggest_subsequence = subsequence;
                    has_max_increased = true;
                }
                continue;
            }

            if (subsequence.back().second < data[i]) {
                auto subsequence_copy = subsequence;
                new_subsequences.emplace_back(subsequence_copy);

                std::pair element(i, data[i]);
                subsequence.emplace_back(element);

                if (subsequence.size() > max_subsequence_size) {
                    max_subsequence_size = static_cast<int>(subsequence.size());
                    biggest_subsequence = subsequence;
                    has_max_increased = true;
                }
            }
        }

        if (!has_max_increased) {
            std::vector<std::pair<int, int>> subsequence{{i, data[i]}};
            available_subsequences.emplace_back(subsequence);
        }

        for (auto& subsequence : new_subsequences) {
            available_subsequences.emplace_back(subsequence);
        }
    }

    return biggest_subsequence;
}


std::vector<std::pair<int, int>> get_biggest_div_subsequence(const std::vector<int>& data, const int k) {
    if (data.empty()) {
        return {};
    }

    std::vector<std::pair<int, int>> sequence = get_sequence_as_pairs(data);

    int sequence_sum = get_vector_sum(data);
    if (sequence_sum % k == 0) {
        return sequence;
    }

    std::vector<std::pair<int, int>> subsequence;
    for (int i = 0; i < data.size(); i++) {
        auto subsequence_copy = data;
        subsequence_copy.erase(subsequence_copy.begin() + i);
        auto biggest_subsequence = get_biggest_div_subsequence(subsequence_copy, k);

        if (biggest_subsequence.size() > subsequence.size()) {
            subsequence = biggest_subsequence;
        }
    }

    return subsequence;
}
















