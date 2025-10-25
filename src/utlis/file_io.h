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

void store_sequence(const std::string& file_path, const std::vector<std::pair<int, int>>& sequence);
void store_graph(const std::string& file_path, const std::vector<std::pair<int, int>>& sequence);
void store_connected_components(const std::string& file_path, const std::vector<std::vector<int>>& components);

#endif //ENSEA_ALGO_TP2_FILE_IO_H
