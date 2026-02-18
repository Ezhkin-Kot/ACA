#include "sorter.h"
#include <iostream>
#include <vector>

void Sorter::QuickSort(std::vector<int> &arr, int left, int right) {
    if (arr.empty()) {
        std::cerr << "Error: array is empty\n";
        return;
    }

    if (left >= right) {
        return;
    }

    int pivot = arr[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (left < j) {
        QuickSort(arr, left, j);
    }
    if (i < right) {
        QuickSort(arr, i, right);
    }
}
