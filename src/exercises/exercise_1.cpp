//
// Created by sebas on 10/25/25.
//

#include "exercise_1.h"

#include <list>


std::vector<std::pair<int, int>> get_biggest_mono_subsequence(const std::vector<int>& data) {
    if (data.empty()) {
        return {};
    }

    std::list<std::vector<std::pair<int, int>>> available_subsequences;
    std::vector<std::pair<int, int>> biggest_subsequence;
    int max_subsequence_size = 0;

    for (int i = 0; i < data.size(); i++) {
        bool has_max_increased{false};
        std::list<std::vector<std::pair<int, int>>> new_subsequences;
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
