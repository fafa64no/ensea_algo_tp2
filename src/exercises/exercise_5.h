//
// Created by sebas on 10/25/25.
//

#ifndef ENSEA_ALGO_TP2_EXERCISE_5_H
#define ENSEA_ALGO_TP2_EXERCISE_5_H

#include <vector>

std::pair<int, std::vector<int>> get_shortest_path(
    const std::vector<std::pair<int, int>>& graph,
    const std::vector<int>& weights,
    int start_label,
    int finish_label
);


std::vector<std::pair<int, std::vector<int>>> get_all_shortest_paths(
    const std::vector<std::pair<int, int>>& graph,
    const std::vector<int>& weights,
    int start_label
);

#endif //ENSEA_ALGO_TP2_EXERCISE_5_H