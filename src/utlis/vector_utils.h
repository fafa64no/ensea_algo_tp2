//
// Created by sebas on 10/22/25.
//

#ifndef ENSEA_ALGO_TP2_VECTOR_UTILS_H
#define ENSEA_ALGO_TP2_VECTOR_UTILS_H

#include <vector>

int get_vector_sum(std::vector<int> data);
int get_vector_sum(std::vector<std::pair<int, int>> data);

std::vector<std::pair<int, int>> get_sequence_as_pairs(std::vector<int> data);

#endif //ENSEA_ALGO_TP2_VECTOR_UTILS_H