//
// Created by sebas on 10/25/25.
//

#include "exercise_3.h"

#include "algo_utils.h"

#include <iostream>
#include <queue>


#ifdef ADJACENCY_LIST_METHOD
std::vector<std::pair<int, int>> get_covering_tree(const std::vector<std::pair<int, int>>& graph) {
    if (graph.empty()) {
        return {};
    }

    std::unordered_map<int,int> id_to_vert;
    std::vector<int> vert_to_id;
    build_label_maps_from_edges(graph, id_to_vert, vert_to_id);
    const int n = static_cast<int>(vert_to_id.size());

    const std::vector<std::vector<int>> adjacency_list = get_adjacency_list(graph, id_to_vert, vert_to_id);

    std::vector<char> visited(n, 0x0);
    std::queue<int> queue;
    std::vector<std::pair<int,int>> tree_edges;

    constexpr int start = 0;
    visited[start] = 1;
    queue.push(start);

    while (!queue.empty()) {
        const int u = queue.front();
        queue.pop();
        for (const int v : adjacency_list[u]) {
            if (visited[v]) {
                continue;
            }
            visited[v] = 1;
            queue.push(v);
            tree_edges.emplace_back(vert_to_id[u], vert_to_id[v]);
            if (static_cast<int>(tree_edges.size()) == n - 1) {
                return tree_edges;
            }
        }
    }

    return tree_edges;
}
#elifdef ADJACENCY_MATRIX_METHOD
std::vector<std::pair<int, int>> get_covering_tree(const std::vector<std::pair<int, int>>& graph) {
    if (graph.empty()) {
        return {};
    }

    std::unordered_map<int,int> id_to_vert;
    std::vector<int> vert_to_id;
    build_label_maps_from_edges(graph, id_to_vert, vert_to_id);
    const int n = static_cast<int>(vert_to_id.size());

    const std::vector<std::vector<int>> adjacency_matrix = get_adjacency_matrix(graph, id_to_vert, vert_to_id);

    std::vector<char> visited(n, 0x0);
    std::queue<int> queue;
    std::vector<std::pair<int,int>> tree_edges;
    tree_edges.reserve(std::max(0, n-1));

    constexpr int start = 0;
    visited[start] = 1;
    queue.push(start);

    while (!queue.empty() && static_cast<int>(tree_edges.size()) < n-1) {
        const int u = queue.front();
        queue.pop();
        for (int v=0; v < n; v++) {
            if (visited[v] || adjacency_matrix[u][v] == 0) {
                continue;
            }
            visited[v] = 1;
            queue.push(v);
            tree_edges.emplace_back(vert_to_id[u], vert_to_id[v]);
            if (static_cast<int>(tree_edges.size()) == n - 1) {
                break;
            }
        }
    }

    return tree_edges;
}
#else
std::vector<std::pair<int, int>> get_covering_tree(const std::vector<std::pair<int, int>>&) {
    std::cerr << "get_covering_tree has no implementation, please uncomment the corresponding #defines in subsequence_finder.h" << std::endl;
    return {};
}
#endif
