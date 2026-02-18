#include "sorter.h"
#include <vector>

void Sorter::QuickSort(std::vector<int> &arr, int left, int right) {
    if (left >= right) {
        return; // Already sorted
    }

    // Set the pivot element as the middle
    int pivot = arr[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        // Find left element greater than pivot
        while (arr[i] < pivot) {
            i++;
        }
        // Find right element less than pivot
        while (arr[j] > pivot) {
            j--;
        }
        // Swap left and right elements if indexes don't cross
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (left < j) {
        // Sort left subarray
        QuickSort(arr, left, j);
    }
    if (i < right) {
        // Sort right subarray
        QuickSort(arr, i, right);
    }
}
