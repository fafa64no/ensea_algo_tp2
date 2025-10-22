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

    return EXIT_SUCCESS;

}
