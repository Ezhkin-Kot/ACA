#include "sort_tester/tester.hpp"
#include "sorter.h"
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
        int elem_counts[] = {50000, 100000, 500000, 1000000};
        for (int i : elem_counts) {
            tester::Tester t1(
                {tester::Config(sorter.QuickSort, 5, i, INT_MIN, INT_MAX)});
            t1.start();
        }
        for (int i : elem_counts) {
            tester::Tester t2(
                {tester::Config(sorter.MergeSort, 5, i, INT_MIN, INT_MAX)});
            t2.start();
        }
        for (int i : elem_counts) {
            tester::Tester t3(
                {tester::Config(sorter.HeapSort, 5, i, INT_MIN, INT_MAX)});
            t3.start();
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
