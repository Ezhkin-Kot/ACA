#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::map<unsigned char, int> bad_char(const std::string &pattern) {
    std::map<unsigned char, int> result;
    int m = static_cast<int>(pattern.length());

    for (int i = 0; i < m; i++) {
        result[static_cast<unsigned char>(pattern[i])] = i;
    }
    return result;
}

std::vector<int> build_suffixes(const std::string &pattern) {
    int m = static_cast<int>(pattern.length());
    std::vector<int> suff(m);

    suff[m - 1] = m;
    int g = m - 1;
    int f = 0;

    for (int i = m - 2; i >= 0; --i) {
        if (i > g && suff[i + m - 1 - f] < i - g) {
            suff[i] = suff[i + m - 1 - f];
        } else {
            if (i < g)
                g = i;
            f = i;
            while (g >= 0 && pattern[g] == pattern[g + m - 1 - f]) {
                --g;
            }
            suff[i] = f - g;
        }
    }
    return suff;
}

std::vector<int> good_suffix(const std::string &pattern) {
    int m = static_cast<int>(pattern.length());
    std::vector<int> result(m, m);
    std::vector<int> suff = build_suffixes(pattern);

    int j = 0;
    for (int i = m - 1; i >= 0; i--) {
        if (suff[i] == i + 1) {
            for (; j < m - 1 - i; j++) {
                if (result[j] == m) {
                    result[j] = m - 1 - i;
                }
            }
        }
    }

    for (int i = 0; i <= m - 2; i++) {
        result[m - 1 - suff[i]] = m - 1 - i;
    }
    return result;
}

std::vector<size_t> boyer_moore_search(const std::string &text,
                                       const std::string &pattern) {
    std::vector<size_t> result;
    size_t n = text.length();
    size_t m = pattern.length();

    if (m == 0 || m > n)
        return result;

    std::map<unsigned char, int> bc = bad_char(pattern);
    std::vector<int> gs = good_suffix(pattern);

    size_t shift = 0;
    while (shift <= n - m) {
        int j = static_cast<int>(m) - 1;

        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        if (j < 0) {
            result.push_back(shift);
            shift += static_cast<size_t>(gs[0]);
        } else {
            unsigned char mismatched_char =
                static_cast<unsigned char>(text[shift + j]);

            int last_pos = -1;
            if (bc.count(mismatched_char)) {
                last_pos = bc[mismatched_char];
            }

            int bc_shift = j - last_pos;
            int gs_shift = gs[j];

            shift += static_cast<size_t>(std::max(bc_shift, gs_shift));
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

    std::vector<size_t> positions = boyer_moore_search(text, pattern);

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
