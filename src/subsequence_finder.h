//
// Created by sebas on 10/22/25.
//

#ifndef ENSEA_ALGO_TP2_SUBSEQUENCE_FINDER_H
#define ENSEA_ALGO_TP2_SUBSEQUENCE_FINDER_H

#include <vector>

std::vector<std::pair<int, int>> get_biggest_mono_subsequence(const std::vector<int>& data);
std::vector<std::pair<int, int>> get_biggest_div_subsequence(const std::vector<int>& data, int k);
std::vector<std::pair<int, int>> get_biggest_div_subsequence(const std::vector<int>& data, int k, int current_sum);

std::vector<std::pair<int, int>> get_covering_tree(const std::vector<std::pair<int, int>>& tree);

#endif //ENSEA_ALGO_TP2_SUBSEQUENCE_FINDER_H
