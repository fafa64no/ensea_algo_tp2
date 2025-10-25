//
// Created by sebas on 10/25/25.
//

#include "exercise_5.h"

#include "algo_utils.h"

#include <iostream>
#include <climits>
#include <queue>

#include "MinHeap.h"


#ifdef DISTANCE_HEAP_METHOD
std::pair<int, std::vector<int>> get_shortest_path(
    const std::vector<std::pair<int, int>>& graph,
    const std::vector<int>& weights,
    const int start_label,
    const int finish_label
) {
    if (graph.empty()) {
        return {0, {}};
    }

    std::unordered_map<int,int> id_to_idx;
    std::vector<int> idx_to_id;
    build_label_maps_from_edges(graph, id_to_idx, idx_to_id);
    const int n = static_cast<int>(idx_to_id.size());

    if (!id_to_idx.contains(start_label) || !id_to_idx.contains(finish_label)) {
        return {INT_MAX, {}};
    }
    const int s = id_to_idx.at(start_label);
    const int t = id_to_idx.at(finish_label);

    std::vector mat(n, std::vector(n, INT_MAX));
    for (int i = 0; i < n; i++) {
        mat[i][i] = 0;
    }
    std::vector<std::vector<std::pair<int, int>>> adjacency(n);
    for (size_t i = 0; i < graph.size(); i++) {
        const int u = id_to_idx[graph[i].first];
        const int v = id_to_idx[graph[i].second];
        const int w = weights[i];
        mat[u][v] = std::min(mat[u][v], w);
        mat[v][u] = mat[u][v];
        adjacency[u].emplace_back(v, w);
        adjacency[v].emplace_back(u, w);
    }

    std::vector dist(n, INT_MAX);
    std::vector prev(n, -1);
    dist[s] = 0;

    MinHeap heap(n, &dist);
    heap.pushOrDecrease(s);

    while (!heap.empty()) {
        const int u = heap.extractMin();
        if (u == t) break;
        for (auto & [v, w] : adjacency[u]) {
            const int nd = dist[u] + w;
            if (nd < dist[v]) {
                dist[v] = nd;
                prev[v] = u;
                heap.pushOrDecrease(v);
            }
        }
    }

    if (dist[t] >= INT_MAX) {
        return {INT_MAX, {}};
    }
    std::vector<int> path;
    for (int cur = t; cur != -1; cur = prev[cur]) {
        path.push_back(idx_to_id[cur]);
    }

    std::reverse(path.begin(), path.end());
    return {dist[t], path};
}
#elifdef ADJACENCY_LIST_METHOD
std::pair<int, std::vector<int>> get_shortest_path(
    const std::vector<std::pair<int, int>>& graph,
    const std::vector<int>& weights,
    const int start_label,
    const int finish_label
) {
    if (graph.empty()) {
        return {0, {}};
    }

    std::unordered_map<int,int> id_to_vert;
    std::vector<int> vert_to_id;
    build_label_maps_from_edges(graph, id_to_vert, vert_to_id);
    const int n = static_cast<int>(vert_to_id.size());

    if (!id_to_vert.contains(start_label) || !id_to_vert.contains(finish_label)) {
        return {INT_MAX, {}};
    }

    const int s = id_to_vert.at(start_label);
    const int t = id_to_vert.at(finish_label);

    std::vector<std::vector<std::pair<int,int>>> adjacency_list(n);
    for (size_t i = 0; i < graph.size(); ++i) {
        const int u = id_to_vert[graph[i].first];
        const int v = id_to_vert[graph[i].second];
        const int w = weights[i];
        adjacency_list[u].emplace_back(v,w);
        adjacency_list[v].emplace_back(u,w);
    }

    std::vector dist(n, INT_MAX);
    std::vector prev(n, -1);
    dist[s] = 0;
    using pli = std::pair<int,int>;
    std::priority_queue<pli, std::vector<pli>, std::greater<>> pq;
    pq.emplace(0, s);

    while (!pq.empty()) {
        auto [d,u] = pq.top();
        pq.pop();
        if (d != dist[u]) {
            continue;
        }
        if (u == t) {
            break;
        }
        for (auto & [v, w] : adjacency_list[u]) {
            const int nd = d + w;
            if (nd < dist[v]) {
                dist[v] = nd;
                prev[v] = u;
                pq.emplace(nd, v);
            }
        }
    }

    if (dist[t] >= INT_MAX) {
        return {INT_MAX, {}};
    }

    std::vector<int> path;
    for (int cur = t; cur != -1; cur = prev[cur]) {
        path.push_back(vert_to_id[cur]);
    }
    
    std::reverse(path.begin(), path.end());
    return {dist[t], path};
}
#elifdef ADJACENCY_MATRIX_METHOD
std::pair<int, std::vector<int>> get_shortest_path(
    const std::vector<std::pair<int, int>>& graph,
    const std::vector<int>& weights,
    const int start_label,
    const int finish_label
) {
    if (graph.empty()) {
        return {0, {}};
    }

    std::unordered_map<int,int> id_to_vert;
    std::vector<int> vert_to_id;
    build_label_maps_from_edges(graph, id_to_vert, vert_to_id);
    const int n = static_cast<int>(vert_to_id.size());

    if (!id_to_vert.contains(start_label) || !id_to_vert.contains(finish_label)) {
        return {INT_MAX, {}};
    }

    const int s = id_to_vert.at(start_label);
    const int t = id_to_vert.at(finish_label);

    std::vector adjacency_matrix(n, std::vector(n, INT_MAX));
    for (int i = 0; i < n; i++) {
        adjacency_matrix[i][i] = 0;
    }
    for (size_t i = 0; i < graph.size(); i++) {
        const int u = id_to_vert[graph[i].first];
        const int v = id_to_vert[graph[i].second];
        const int w = weights[i];
        if (w < adjacency_matrix[u][v]) {
            adjacency_matrix[u][v] = adjacency_matrix[v][u] = w;
        }
    }

    std::vector dist(n, INT_MAX);
    std::vector prev(n, -1);
    std::vector<char> used(n, 0);
    dist[s] = 0;

    for (int it = 0; it < n; it++) {
        int u = -1;
        int best = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!used[i] && dist[i] < best) {
                best = dist[i]; u = i;
            }
        }
        if (u == -1) {
            break;
        }
        used[u] = 1;
        for (int v = 0; v < n; ++v) {
            if (adjacency_matrix[u][v] < INT_MAX && !used[v]) {
                const int nd = dist[u] + adjacency_matrix[u][v];
                if (nd < dist[v]) {
                    dist[v] = nd;
                    prev[v] = u;
                }
            }
        }
    }

    if (dist[t] >= INT_MAX) {
        return {INT_MAX, {}};
    }

    std::vector<int> path;
    for (int cur = t; cur != -1; cur = prev[cur]) {
        path.push_back(vert_to_id[cur]);
    }

    std::reverse(path.begin(), path.end());
    return {dist[t], path};
}
#else
std::pair<int, std::vector<int>> get_shortest_path(
    const std::vector<std::pair<int, int>>& graph,
    const std::vector<int>& weights,
    const int start_label,
    const int finish_label
) {
    std::cerr << "get_shortest_path has no implementation, please uncomment the corresponding #defines in algo_utils.h" << std::endl;
    return {};
}
#endif








