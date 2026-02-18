#include "sorter.h"
#include <iostream>

int main() {
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
    return 0;
}
