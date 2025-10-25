//
// Created by sebas on 10/22/25.
//

#ifndef ENSEA_ALGO_TP2_FILE_IO_H
#define ENSEA_ALGO_TP2_FILE_IO_H

#include <string>
#include <vector>

std::string read_file(const std::string& file_path);
std::vector<int> read_sequence(const std::string& file_path);
std::vector<std::pair<int, int>> read_tree(const std::string& file_path);
void read_weighted_tree(const std::string& file_path, std::vector<std::pair<int, int>>& tree, std::vector<int>& weights);

void store_sequence(const std::string& file_path, const std::vector<std::pair<int, int>>& sequence);
void store_sequence_with_sum(const std::string& file_path, const std::vector<std::pair<int, int>>& sequence);
void store_graph(const std::string& file_path, const std::vector<std::pair<int, int>>& sequence);
void store_connected_components(const std::string& file_path, const std::vector<std::vector<int>>& components);
void store_path(const std::string& file_path, int path_length, const std::vector<int>& path);
void store_paths(const std::string& file_path, const std::vector<std::pair<int, std::vector<int>>>& paths);

#endif //ENSEA_ALGO_TP2_FILE_IO_H
