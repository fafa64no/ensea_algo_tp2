//
// Created by sebas on 10/25/25.
//

#include "exercise_4.h"

#include "algo_utils.h"

#include <iostream>
#include <queue>


#ifdef ADJACENCY_LIST_METHOD
std::vector<std::vector<int>> get_connected_components(const std::vector<std::pair<int, int>>& graph) {
    if (graph.empty()) {
        return {};
    }

    std::unordered_map<int,int> id_to_vert;
    std::vector<int> vert_to_id;
    build_label_maps_from_edges(graph, id_to_vert, vert_to_id);
    const int n = static_cast<int>(vert_to_id.size());

    const std::vector<std::vector<int>> adjacency_list = get_adjacency_list(graph, id_to_vert, vert_to_id);

    std::vector<char> visited(n, 0);
    std::vector<std::vector<int>> components;
    components.reserve(n);

    for (int s = 0; s < n; ++s) {
        if (visited[s]) {
            continue;
        }

        std::vector<int> comp;
        std::queue<int> q;
        visited[s] = 1;
        q.push(s);

        while (!q.empty()) {
            const int u = q.front();
            q.pop();
            comp.push_back(vert_to_id[u]);

            for (int v : adjacency_list[u]) {
                if (visited[v]) {
                    continue;
                }
                visited[v] = 1;
                q.push(v);
            }
        }
        components.push_back(std::move(comp));
    }

    return components;
}
#elifdef ADJACENCY_MATRIX_METHOD
std::vector<std::vector<int>> get_connected_components(const std::vector<std::pair<int, int>>& graph) {
    if (graph.empty()) {
        return {};
    }

    std::unordered_map<int,int> id_to_vert;
    std::vector<int> vert_to_id;
    build_label_maps_from_edges(graph, id_to_vert, vert_to_id);
    int n = static_cast<int>(vert_to_id.size());

    const std::vector<std::vector<int>> adjacency_matrix = get_adjacency_matrix(graph, id_to_vert, vert_to_id);

    std::vector<char> visited(n, 0);
    std::vector<std::vector<int>> components;
    components.reserve(n);

    for (int s = 0; s < n; s++) {
        if (visited[s]) continue;
        std::vector<int> comp;
        std::queue<int> q;
        visited[s] = 1;
        q.push(s);
        while (!q.empty()) {
            const int u = q.front();
            q.pop();
            comp.push_back(vert_to_id[u]);
            for (int v = 0; v < n; v++) {
                if (visited[v] || adjacency_matrix[u][v] == 0) {
                    continue;
                }
                visited[v] = 1;
                q.push(v);
            }
        }
        components.push_back(std::move(comp));
    }

    return components;
}
#else
std::vector<std::vector<int>> get_connected_components(const std::vector<std::pair<int, int>>&) {
    std::cerr << "get_connected_components has no implementation, please uncomment the corresponding #defines in subsequence_finder.h" << std::endl;
    return {};
}
#endif

