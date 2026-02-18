#include "sorter.h"
#include <iostream>
#include <vector>

void heapify(std::vector<int> &arr, int n, int i) {
    int max = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[max]) {
        max = left;
    }
    if (right < n && arr[right] > arr[max]) {
        max = right;
    }
    if (max != i) {
        std::swap(arr[i], arr[max]);
        heapify(arr, n, max);
    }
}

void Sorter::HeapSort(std::vector<int> &arr) {
    if (arr.empty()) {
        std::cerr << "Error: array is empty\n";
        return;
    }

    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
