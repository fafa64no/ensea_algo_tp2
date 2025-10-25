//
// Created by sebas on 10/22/25.
//

#include "file_io.h"

#include <fstream>
#include <sstream>
#include <pstl/execution_defs.h>


std::string read_file(const std::string& file_path) {
    std::string data;

    std::ifstream file_handle(file_path);
    std::ostringstream buffer;
    buffer << file_handle.rdbuf();
    file_handle.close();

    data = buffer.str();
    return data;
}

std::vector<int> read_sequence(const std::string& file_path) {
    std::vector<int> seq;
    const auto file_contents = read_file(file_path);

    int last_value = 0;
    bool reading = false;
    for (const auto& c : file_contents) {
        if (c >= '0' && c <= '9') {
            last_value *= 10;
            last_value += c - '0';
            reading = true;
        } else {
            seq.emplace_back(last_value);
            last_value = 0;
            reading = false;
        }
    }

    if (reading) {
        seq.emplace_back(last_value);
    }

    return seq;
}

std::vector<std::pair<int, int>> read_tree(const std::string& file_path) {
    std::vector<std::pair<int, int>> tree;
    const auto file_contents = read_file(file_path);

    int last_value = 0;
    bool reading = false;
    bool reading_first_value = true;
    std::pair<int, int> last;
    for (const auto& c : file_contents) {
        if (c >= '0' && c <= '9') {
            last_value *= 10;
            last_value += c - '0';
            reading = true;
        } else {
            if (reading_first_value) {
                last.first = last_value;
                reading_first_value = false;
            } else {
                last.second = last_value;
                reading_first_value = true;
                tree.emplace_back(last);
            }
            last_value = 0;
            reading = false;
        }
    }

    if (reading && !reading_first_value) {
        last.second = last_value;
        tree.emplace_back(last);
    }

    return tree;
}


void store_sequence(const std::string& file_path, const std::vector<std::pair<int, int>>& sequence) {
    std::ofstream file_handle(file_path);

    file_handle << "Sequence has length: " << sequence.size() << std::endl;
    for (const auto&[fst, snd] : sequence) {
        file_handle << "a[" << fst << "] = " << snd << std::endl;
    }

    file_handle.close();
}




