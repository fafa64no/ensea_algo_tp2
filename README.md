# Authors
This repository is a collaborative work of Sébastien Nouira--Huet && Yaël Cavaillé-Voisin.
# Algorithm

This repository is used for the TP2 of the Algorithm course at ENSEA.

## Compilation

This project was compiled with C++ 23 and CLion on linux.

It uses [CMakeLists.txt](CMakeLists.txt), and depending on how you compile it, you might need to change
the paths in [magic_numbers.h](src/magic_numbers.h).

## Changing between adjacency matrix and adjacency list

The method used for implementation is defined in 
[algo_utils.h](src/utlis/algo_utils.h).

## Questions

Regarding question 5.4:

5.2 has lower complexity than 5.1.

If E is the number of edges, V the number of vertex, with V > E, then:
- 5.1 is O(V²)
- 5.2 is O(E * log(V))






