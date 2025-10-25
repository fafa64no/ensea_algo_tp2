//
// Created by sebas on 10/25/25.
//

#ifndef ENSEA_ALGO_TP2_MINHEAP_H
#define ENSEA_ALGO_TP2_MINHEAP_H

#include <vector>


class MinHeap {
public:
    MinHeap(int n, std::vector<int>* key_ptr);

    [[nodiscard]] bool empty() const;
    void swap_nodes(int i, int j);
    void siftUp(int i);
    void siftDown(int i);
    void pushOrDecrease(int v);
    int extractMin();
private:
    std::vector<int> heap;
    std::vector<int> pos;
    std::vector<int>* key;
};


#endif //ENSEA_ALGO_TP2_MINHEAP_H