#include <iostream>
#include <vector>

#include "file_io.h"
#include "magic_numbers.h"
#include "subsequence_finder.h"

int main() {
    const auto data = read_sequence(DEFAULT_FILE_INPUT_PATH);
    const auto subsequence = get_biggest_mono_subsequence(data);
    store_sequence(DEFAULT_FILE_OUTPUT_PATH, subsequence);

    return EXIT_SUCCESS;

}
