//
// Created by sebas on 10/25/25.
//

#include "MinHeap.h"

#include <iostream>
#include <ostream>


MinHeap::MinHeap(const int n, std::vector<int>* key_ptr) : pos(n, -1), key(key_ptr) {

}


bool MinHeap::empty() const {
    return heap.empty();
}

void MinHeap::swap_nodes(const int i, const int j) {
    std::swap(heap[i], heap[j]);
    pos[heap[i]] = i;
    pos[heap[j]] = j;
}

void MinHeap::siftUp(int i) {
    while (i > 0) {
        const int p = (i - 1) >> 1;
        if ((*key)[heap[i]] < (*key)[heap[p]]) {
            swap_nodes(i,p);
            i = p;
        } else {
            break;
        }
    }
}

void MinHeap::siftDown(int i) {
    const int n = static_cast<int>(heap.size());
    while (true) {
        const int l{i*2 + 1}, r{i*2 + 2};
        int smallest = i;
        if (l<n && (*key)[heap[l]] < (*key)[heap[smallest]]) {
            smallest = l;
        }
        if (r<n && (*key)[heap[r]] < (*key)[heap[smallest]]) {
            smallest = r;
        }
        if (smallest != i) {
            swap_nodes(i, smallest);
            i = smallest;
        } else {
            break;
        }
    }
}

void MinHeap::pushOrDecrease(const int v) {
    if (pos[v] == -1) {
        pos[v] = static_cast<int>(heap.size());
        heap.push_back(v);
        siftUp(pos[v]);
    } else {
        siftUp(pos[v]);
    }
}

int MinHeap::extractMin() {
    if (empty()) {
        std::cerr << "MinHeap::extractMin: Can't extract from empty heap" << std::endl;
        return 0;
    }
    const int res = heap[0];
    const int last = heap.back();
    pos[res] = -1;
    heap.pop_back();
    if (!heap.empty()) {
        heap[0] = last;
        pos[last] = 0;
        siftDown(0);
    }
    return res;
}










