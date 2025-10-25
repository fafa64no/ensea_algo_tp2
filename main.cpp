#include <iostream>
#include <vector>

#include "file_io.h"
#include "magic_numbers.h"
#include "subsequence_finder.h"

int main() {
    {
        const auto data = read_sequence(DEFAULT_MONO_INPUT_PATH);
        const auto subsequence = get_biggest_mono_subsequence(data);
        store_sequence(DEFAULT_MONO_OUTPUT_PATH, subsequence);
    }

    {
        const auto data = read_sequence(DEFAULT_DIV_INPUT_PATH);
        const auto subsequence = get_biggest_div_subsequence(data, 5);
        store_sequence(DEFAULT_DIV_OUTPUT_PATH, subsequence);
    }

    {
        const auto data = read_tree(DEFAULT_ARB_INPUT_PATH);
        const auto covering_tree = get_covering_tree(data);
        store_sequence(DEFAULT_ARB_OUTPUT_PATH, covering_tree);
    }

    {
        const auto data = read_tree(DEFAULT_CON_OUTPUT_PATH);
    }

    {
        const auto data = read_tree(DEFAULT_DIJ_OUTPUT_PATH);
    }

    return EXIT_SUCCESS;

}
