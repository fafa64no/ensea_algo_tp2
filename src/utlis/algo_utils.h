//
// Created by sebas on 10/25/25.
//

#ifndef ENSEA_ALGO_TP2_ALGO_UTILS_H
#define ENSEA_ALGO_TP2_ALGO_UTILS_H

#include <unordered_map>
#include <vector>

#define DISTANCE_HEAP_METHOD    // Comment this to disable heap method
#define ADJACENCY_LIST_METHOD   // Comment this to disable adjacency list method
#define ADJACENCY_MATRIX_METHOD // Comment this to disable adjacency matrix method

void build_label_maps_from_edges(
    const std::vector<std::pair<int, int>>& graph,
    std::unordered_map<int,int>& id_to_vert,
    std::vector<int>& vert_to_id
);
std::vector<std::vector<int>> get_adjacency_list(
    const std::vector<std::pair<int, int>>& graph,
    const std::unordered_map<int,int>& id_to_vert,
    const std::vector<int>& vert_to_id
);
std::vector<std::vector<int>> get_adjacency_matrix(
    const std::vector<std::pair<int, int>>& graph,
    const std::unordered_map<int,int>& id_to_vert,
    const std::vector<int>& vert_to_id
);

#endif //ENSEA_ALGO_TP2_ALGO_UTILS_H