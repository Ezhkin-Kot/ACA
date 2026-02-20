#include "sorter.h"
#include "tester.h"
#include <iostream>

int main() {
    bool test_mode = false;
    std::cout << "Run tests? (y/n) ";
    char choice;
    std::cin >> choice;
    if (choice == 'y') {
        test_mode = true;
    }

    if (test_mode) {
        Sorter sorter;
        double time;
        int elem_counts[] = {50000, 100000, 500000, 1000000};
        for (int i : elem_counts) {
            time = MeasureSortTime(sorter.QuickSort, i, 5);
            std::cout << "Quick sort time for " << i << " elements: " << time
                      << "\n";
        }
        for (int i : elem_counts) {
            time = MeasureSortTime(sorter.MergeSort, i, 5);
            std::cout << "Merge sort time for " << i << " elements: " << time
                      << "\n";
        }
        for (int i : elem_counts) {
            time = MeasureSortTime(sorter.HeapSort, i, 5);
            std::cout << "Heap sort time for " << i << " elements: " << time
                      << "\n";
        }
    } else {
        int n;
        std::cout << "Enter the number of elements: ";
        std::cin >> n;

        std::vector<int> arr(n);
        std::cout << "Enter the elements:\n";
        for (int i = 0; i < n; i++) {
            std::cin >> arr[i];
        }

        Sorter sorter;
        sorter.SortArray(arr); // Select sorting algorithm

        for (int i = 0; i < arr.size(); i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
