//
// Created by sebas on 10/25/25.
//

#include "algo_utils.h"


void build_label_maps_from_edges(
    const std::vector<std::pair<int, int>>& graph,
    std::unordered_map<int,int>& id_to_vert,
    std::vector<int>& vert_to_id
) {
    if (graph.empty()) {
        return;
    }

    id_to_vert.reserve(graph.size() * 2);
    for (const auto & [fst, snd] : graph) {
        int a = fst, b = snd;
        if (!id_to_vert.contains(a)) {
            id_to_vert[a] = static_cast<int>(vert_to_id.size());
            vert_to_id.push_back(a);
        }
        if (!id_to_vert.contains(b)) {
            id_to_vert[b] = static_cast<int>(vert_to_id.size());
            vert_to_id.push_back(b);
        }
    }
}

std::vector<std::vector<int>> get_adjacency_list(
    const std::vector<std::pair<int, int>>& graph,
    const std::unordered_map<int,int>& id_to_vert,
    const std::vector<int>& vert_to_id
) {
    const int n = static_cast<int>(vert_to_id.size());
    std::vector<std::vector<int>> adjacency_list(n);
    adjacency_list.assign(n, {});
    for (const auto & [fst, snd] : graph) {
        const int u = id_to_vert.at(fst);
        const int v = id_to_vert.at(snd);
        adjacency_list[u].push_back(v);
        adjacency_list[v].push_back(u);
    }
    return adjacency_list;
}

std::vector<std::vector<int>> get_adjacency_matrix(
    const std::vector<std::pair<int, int>>& graph,
    const std::unordered_map<int,int>& id_to_vert,
    const std::vector<int>& vert_to_id
) {
    const int n = static_cast<int>(vert_to_id.size());
    std::vector adjacency_matrix(n, std::vector(n, 0));
    for (const auto & [fst, snd] : graph) {
        const int u = id_to_vert.at(fst);
        const int v = id_to_vert.at(snd);
        adjacency_matrix[u][v] += 1;
        adjacency_matrix[v][u] += 1;
    }
    return adjacency_matrix;
}








