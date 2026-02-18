#pragma once
#include <iostream>
#include <vector>

struct Sorter {
    static void QuickSort(std::vector<int> &arr);
    static void MergeSort(std::vector<int> &arr);
    static void HeapSort(std::vector<int> &arr);

    static void SortArray(std::vector<int> &arr) {
        char choice;
        std::cout << "Sorting methods:\n";
        std::cout << "1. Quick sort\n";
        std::cout << "2. Merge sort\n";
        std::cout << "3. Pyramid sort\n";
        std::cout << "Choose sorting method (1, 2, 3): ";
        std::cin >> choice;

        switch (choice) {
        case '1':
            QuickSort(arr);
            break;
        case '2':
            MergeSort(arr);
            break;
        case '3':
            HeapSort(arr);
            break;
        default:
            std::cerr << "Error: invalid input\n";
        }
    }
};
