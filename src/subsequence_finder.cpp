//
// Created by sebas on 10/22/25.
//

#include "subsequence_finder.h"

#include <iostream>
#include <climits>
#include <list>
#include <ostream>
#include <queue>
#include <ranges>


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


std::vector<std::pair<int, int>> get_biggest_div_subsequence(const std::vector<int>& data, const int k) {
    if (data.empty() || k <= 0) {
        return {};
    }

    const int n = static_cast<int>(data.size());
    // depth[i][r] = maximum number of elements we can pick from first i elements such that sum % k == r
    // taken[i][r] = whether the optimal depth[i][r] was obtained by taking element i-1
    // prev_rem[i][r] = previous remainder in the transition to (i, r)
    std::vector depth(n+1, std::vector(k, INT_MIN));
    std::vector taken(n+1, std::vector<char>(k, 0));
    std::vector prev_rem(n+1, std::vector(k, -1));

    depth[0][0] = 0;
    for (int r = 1; r < k; r++) {
        depth[0][r] = INT_MIN;
    }

    for (int i = 0; i < n; i++) {
        for (int r = 0; r < k; ++r) {
            depth[i+1][r] = depth[i][r];
            taken[i+1][r] = 0;
            prev_rem[i+1][r] = r;
        }

        const int add = (data[i] + k) % k;
        for (int r = 0; r < k; ++r) {
            if (depth[i][r] == INT_MIN) {
                continue;
            }
            const int newr = (r + add) % k;
            const int cand = depth[i][r] + 1;
            if (cand > depth[i+1][newr]) {
                depth[i+1][newr] = cand;
                taken[i+1][newr] = 1;
                prev_rem[i+1][newr] = r;
            }
        }
    }

    if (depth[n][0] <= 0) {
        return {};
    }

    std::vector<std::pair<int,int>> result; result.reserve(depth[n][0]);
    int i = n;
    int rem = 0;
    while (i > 0) {
        if (taken[i][rem]) {
            result.emplace_back(i, data[i-1]);
            const int prev = prev_rem[i][rem];
            rem = prev;
            i = i - 1;
        } else {
            const int prev = prev_rem[i][rem];
            rem = prev;
            i = i - 1;
        }
    }

    return result;
}


void get_vertex_occurrences(
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


#ifdef ADJACENCY_LIST_METHOD
std::vector<std::pair<int, int>> get_covering_tree(const std::vector<std::pair<int, int>>& graph) {
    if (graph.empty()) {
        return {};
    }

    std::unordered_map<int,int> id_to_vert;
    std::vector<int> vert_to_id;
    get_vertex_occurrences(graph, id_to_vert, vert_to_id);
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
    get_vertex_occurrences(graph, id_to_vert, vert_to_id);
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

#ifdef ADJACENCY_LIST_METHOD
std::vector<std::vector<int>> get_connected_components(const std::vector<std::pair<int, int>>& graph) {
    if (graph.empty()) {
        return {};
    }

    std::unordered_map<int,int> id_to_vert;
    std::vector<int> vert_to_id;
    get_vertex_occurrences(graph, id_to_vert, vert_to_id);
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
    get_vertex_occurrences(graph, id_to_vert, vert_to_id);
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









