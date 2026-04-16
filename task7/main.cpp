#include <iostream>
#include <vector>

std::vector<size_t> prefix_function(const std::string &s) {
    size_t n = s.length();
    std::vector<size_t> pi(n, 0);

    for (size_t i = 1; i < n; i++) {
        size_t j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }

    return pi;
}

std::vector<size_t> kmp_search(const std::string &text,
                               const std::string &pattern) {
    std::vector<size_t> result;
    size_t n = text.length();
    size_t m = pattern.length();

    if (m == 0)
        return result;

    std::vector<size_t> pi = prefix_function(pattern);

    size_t i = 0;
    size_t j = 0;
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;

            if (j == m) {
                result.push_back(i - j);
                j = pi[j - 1];
            }
        } else {
            if (j != 0) {
                j = pi[j - 1];
            } else {
                i++;
            }
        }
    }

    return result;
}

int main() {
    std::string text, pattern;
    std::cout << "Enter the string: ";
    std::cin >> text;
    std::cout << "Enter the pattern: ";
    std::cin >> pattern;

    std::vector<size_t> positions = kmp_search(text, pattern);

    if (positions.empty()) {
        std::cout << "Pattern not found." << std::endl;
    } else {
        std::cout << "Found: " << positions.size() << std::endl;
        std::cout << "Positions: ";
        for (size_t pos : positions)
            std::cout << pos << " ";
        std::cout << std::endl;
    }

    return 0;
}
