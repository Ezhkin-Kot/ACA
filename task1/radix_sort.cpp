#include <iostream>
#include <vector>

// Sort the array by specific digit
void countingSort(std::vector<int> &arr, int exp) {
    int n = arr.size();
    std::vector<int> count(10, 0);
    std::vector<int> result(n);

    // Count the frequency of each digit in the array
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    // Calculate the cumulative count
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Place the elements in the sorted order
    for (int i = n - 1; i >= 0; i--) {
        result[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    arr = result;
}

// LSD Radix Sort with O(d(n + k))
// d = max number of digits, n = number of elements, k = radix (= 10)
void radixSort(std::vector<int> &arr) {
    if (arr.empty()) {
        std::cerr << "Error: array is empty\n";
        return;
    }

    // Find the max element of the array
    // to determine the max number of digits
    int max = arr[0];
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < 0) {
            std::cerr << "Error: array contains negative numbers\n";
            return;
        }
    }

    // Sort the array using counting sort for each digit
    // from the least significant digit (LSD)
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(arr, exp);
    }
}

int main() {
    int n;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;

    std::vector<int> arr(n);
    std::cout << "Enter the elements:\n";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    radixSort(arr);

    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
