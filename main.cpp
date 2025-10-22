#include <iostream>
#include <vector>

#include "subsequence_finder.h"

int main() {
    const std::vector data = {11, 1, 2, 3, 8, 9, 4, 5, 6, 20, 9, 10};
    const auto subsequence = get_biggest_subsequence(data);

    std::cout << "Biggest sequence has length: " << subsequence.size() << std::endl;
    for (const auto&[fst, snd] : subsequence) {
        std::cout << "a[" << fst << "] = " << snd << std::endl;
    }

    return EXIT_SUCCESS;

}
