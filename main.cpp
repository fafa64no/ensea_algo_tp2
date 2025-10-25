#include "file_io.h"
#include "magic_numbers.h"
#include "exercise_1.h"
#include "exercise_2.h"
#include "exercise_3.h"
#include "exercise_4.h"
#include "exercise_5.h"


int main() {
    {
        const auto data = read_sequence(DEFAULT_MONO_INPUT_PATH);
        const auto subsequence = get_biggest_mono_subsequence(data);
        store_sequence(DEFAULT_MONO_OUTPUT_PATH, subsequence);
    }

    {
        const auto data = read_sequence(DEFAULT_DIV_INPUT_PATH);
        const auto subsequence = get_biggest_div_subsequence(data, 5);
        store_sequence_with_sum(DEFAULT_DIV_OUTPUT_PATH, subsequence);
    }

    {
        const auto data = read_tree(DEFAULT_ARB_INPUT_PATH);
        const auto covering_tree = get_covering_tree(data);
        store_graph(DEFAULT_ARB_OUTPUT_PATH, covering_tree);
    }

    {
        const auto data = read_tree(DEFAULT_CON_INPUT_PATH);
        const auto covering_tree = get_connected_components(data);
        store_connected_components(DEFAULT_CON_OUTPUT_PATH, covering_tree);
    }

    {
        const std::vector<std::pair<int, int>> graph = {
            {1, 2},
            {1, 6},
            {2, 3},
            {3, 4},
            {3, 6},
            {5, 4},
            {6, 5},
        };
        const std::vector<int> wieghts = {
            1, 20, 2, 20, 3, 5, 4
        };
        const auto [path_length, path] = get_shortest_path(graph, wieghts, 1, 4);
        /// TODO:
        /// - read data
        /// - apply algorithm
        /// - store data
    }

    return EXIT_SUCCESS;

}
