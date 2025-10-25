//
// Created by sebas on 10/25/25.
//

#include "exercise_1.h"

#include <algorithm>
#include <list>


std::vector<std::pair<int, int>> get_biggest_mono_subsequence(const std::vector<int>& data) {
    if (data.empty()) {
        return {};
    }

    const int n = static_cast<int>(data.size());

    std::vector prev(n, -1);

    std::vector<int> tails_vals;
    std::vector<int> tails_idx;
    tails_vals.reserve(n);
    tails_idx.reserve(n);

    int best_len = 0;
    int best_tail_idx = -1;

    for (int i = 0; i < n; i++) {
        int x = data[i];
        // std::ranges::lower_bound finds the first index of the vector where we can place x
        // without changing the vector's order
        auto it = std::ranges::lower_bound(tails_vals, x);
        const int len = static_cast<int>(it - tails_vals.begin());

        if (it == tails_vals.end()) {
            tails_vals.push_back(x);
            tails_idx.push_back(i);
        } else {
            *it = x;
            tails_idx[len] = i;
        }

        if (len > 0) {
            prev[i] = tails_idx[len - 1];
        } else {
            prev[i] = -1;
        }

        if (len + 1 > best_len) {
            best_len = len + 1;
            best_tail_idx = i;
        }
    }

    std::vector<std::pair<int,int>> res;
    if (best_len == 0) {
        return res;
    }

    int cur = best_tail_idx;
    while (cur != -1) {
        res.emplace_back(cur, data[cur]);
        cur = prev[cur];
    }
    std::ranges::reverse(res);
    return res;
}
