//
// Created by sebas on 10/22/25.
//

#include "subsequence_finder.h"

#include <list>
#include <queue>
#include <ranges>
#include <unordered_map>

#include "vector_utils.h"


std::vector<std::pair<int, int>> get_biggest_mono_subsequence(const std::vector<int>& data) {
    if (data.empty()) {
        return {};
    }

    std::list<std::vector<std::pair<int, int>>> available_subsequences;
    std::vector<std::pair<int, int>> biggest_subsequence;
    int max_subsequence_size = 0;

    for (int i = 0; i < data.size(); i++) {
        bool has_max_increased{false};
        std::list<std::vector<std::pair<int, int>>> new_subsequences;;
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
    // New algo to try
    // - get nb of occurrence of each value
    // - get total sum
    // - read from occurrences list what you can remove to get dividable sum

    if (data.empty()) {
        return {};
    }

    int sequence_sum = get_vector_sum(data);
    if (sequence_sum % k == 0) {
        return get_sequence_as_pairs(data);
    }

    std::vector<std::pair<int, int>> sequence = get_sequence_as_pairs(data);

    std::vector<std::pair<int, int>> subsequence;
    for (int i = 0; i < data.size(); i++) {
        auto subsequence_copy = data;
        subsequence_copy.erase(subsequence_copy.begin() + i);
        auto biggest_subsequence = get_biggest_div_subsequence(
            subsequence_copy,
            k,
            sequence_sum - data[i]
        );

        if (biggest_subsequence.size() > subsequence.size()) {
            subsequence = biggest_subsequence;
        }
    }

    return subsequence;
}

std::vector<std::pair<int, int>> get_biggest_div_subsequence(const std::vector<int>& data, const int k, const int current_sum) {
    if (data.empty()) {
        return {};
    }

    if (current_sum % k == 0) {
        return get_sequence_as_pairs(data);
    }

    std::vector<std::pair<int, int>> sequence = get_sequence_as_pairs(data);

    std::vector<std::pair<int, int>> subsequence;
    for (int i = 0; i < data.size(); i++) {
        auto subsequence_copy = data;
        subsequence_copy.erase(subsequence_copy.begin() + i);
        auto biggest_subsequence = get_biggest_div_subsequence(subsequence_copy, k);

        if (biggest_subsequence.size() > subsequence.size()) {
            subsequence = biggest_subsequence;
        }
    }

    return subsequence;
}


#ifdef ADJACENCY_LIST_METHOD
std::vector<std::pair<int, int>> get_covering_tree(const std::vector<std::pair<int, int>>& tree) {
    // Uses the "Breadth-First Search" algorithm
    if (tree.empty()) {
        return {};
    }

    std::unordered_map<int,int> id_to_vert;
    std::vector<int> vert_to_id;

    id_to_vert.reserve(tree.size() * 2);
    for (const auto & [fst, snd] : tree) {
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
    const int n = static_cast<int>(vert_to_id.size());

    std::vector<std::vector<int>> adjacency_list(n);
    adjacency_list.assign(n, {});
    for (const auto & [fst, snd] : tree) {
        const int u = id_to_vert.at(fst);
        const int v = id_to_vert.at(snd);
        adjacency_list[u].push_back(v);
        adjacency_list[v].push_back(u);
    }

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
#else
std::vector<std::pair<int, int>> get_covering_tree(const std::vector<std::pair<int, int>>& tree) {
    // Uses the "Breadth-First Search" algorithm
    if (tree.empty()) {
        return {};
    }

    std::unordered_map<int,int> id_to_vert;
    std::vector<int> vert_to_id;

    id_to_vert.reserve(tree.size() * 2);
    for (const auto & [fst, snd] : tree) {
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
    const int n = static_cast<int>(vert_to_id.size());

    std::vector<std::vector<int>> adjacency_matrix(n, std::vector<int>(n, 0));
    for (const auto & [fst, snd] : tree) {
        const int u = id_to_vert.at(fst);
        const int v = id_to_vert.at(snd);
        adjacency_matrix[u][v] += 1;
        adjacency_matrix[v][u] += 1;
    }

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
#endif










