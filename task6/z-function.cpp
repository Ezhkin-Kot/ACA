#include <iostream>
#include <vector>

std::vector<int> z_function(std::string s) {
    int n = (int)s.length();
    std::vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    std::string s;
    std::cout << "Enter the string: ";
    std::cin >> s;
    std::vector<int> z = z_function(s);
    std::cout << "Z function: ";
    for (int i = 0; i < z.size(); i++) {
        std::cout << z[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
