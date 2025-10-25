//
// Created by sebas on 10/25/25.
//

#include "exercise_2.h"

#include <climits>


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
