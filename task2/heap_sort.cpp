#include "sorter.h"
#include <vector>

// Create a heap from the subarray
void heapify(std::vector<int> &arr, int n, int i) {
    int max = i; // Node i is the root
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[max]) {
        // If the left child is greater than the root
        max = left;
    }
    if (right < n && arr[right] > arr[max]) {
        // If the right child is greater than the root
        max = right;
    }
    if (max != i) {
        // If the max is not the root
        std::swap(arr[i], arr[max]);
        heapify(arr, n, max);
    }
}

void Sorter::HeapSort(std::vector<int> &arr) {
    int n = arr.size();
    // Build the heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Sort the array
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
