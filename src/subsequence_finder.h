//
// Created by sebas on 10/22/25.
//

#ifndef ENSEA_ALGO_TP2_SUBSEQUENCE_FINDER_H
#define ENSEA_ALGO_TP2_SUBSEQUENCE_FINDER_H

#include <unordered_map>
#include <vector>

#define ADJACENCY_LIST_METHOD   // Comment this to disable adjacency list method
#define ADJACENCY_MATRIX_METHOD // Comment this to disable adjacency matrix method

std::vector<std::pair<int, int>> get_biggest_mono_subsequence(const std::vector<int>& data);
std::vector<std::pair<int, int>> get_biggest_div_subsequence(const std::vector<int>& data, int k);

void get_vertex_occurrences(
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

std::vector<std::pair<int, int>> get_covering_tree(const std::vector<std::pair<int, int>>& graph);
std::vector<std::vector<int>> get_connected_components(const std::vector<std::pair<int, int>>& graph);

#endif //ENSEA_ALGO_TP2_SUBSEQUENCE_FINDER_H
