//
// Created by sebas on 10/25/25.
//

#include "exercise_5.h"

#include "algo_utils.h"

#include <iostream>

#ifdef ADJACENCY_LIST_METHOD
/// TODO
#elifdef ADJACENCY_MATRIX_METHOD
/// TODO
#else
std::pair<int, std::vector<int>> get_shortest_path(
    const std::vector<std::pair<int, int>>& edges,
    const std::vector<int>& weights,
    int start_label,
    int finish_label
) {
    std::cerr << "get_shortest_path has no implementation, please uncomment the corresponding #defines in algo_utils.h" << std::endl;
    return {};
}
#endif








