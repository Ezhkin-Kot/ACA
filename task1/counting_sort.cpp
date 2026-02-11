#include <iostream>
#include <vector>

// Counting Sort with O(n + k)
// n = number of elements, k = range between elements
void countingSort(std::vector<int> &arr) {
    if (arr.empty()) {
        std::cout << "Error: array is empty" << std::endl;
        return;
    }

    // Find the max range between elements of the array
    int max = arr[0];
    int min = arr[0];
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    int range = max - min + 1;

    // Count the frequency of each element
    std::vector<int> count(range, 0);
    for (int i = 0; i < n; i++) {
        count[arr[i] - min]++;
    }

    // Calculate the cumulative count
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    // Place the elements in sorted order
    std::vector<int> result(n);
    for (int i = n - 1; i >= 0; i--) {
        // Use reverse indexing for stable sort
        result[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }

    arr = result;
}

int main() {
    int n;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;

    std::vector<int> arr(n);
    std::cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    countingSort(arr);

    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
