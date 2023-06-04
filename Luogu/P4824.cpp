//HZ - 37.8
//Luogu - P4824
#include <bits/stdc++.h>

constexpr int maxN = 1e6 + 5;

std::array<int, maxN> prefix, match;
std::list<int> data;

int main() {
    std::string text, pattern;

    std::cin >> text >> pattern;

    int const patternLength = (int) pattern.length();
    int const textLength = (int) text.length();

    for (int i = 0; i < textLength; ++i)
        data.push_back(i);

    for (int i = 1; i < patternLength; ++i) {
        int j = prefix[i - 1];

        while (j > 0 && pattern[i] != pattern[j])
            j = prefix[j - 1];

        if (pattern[i] == pattern[j])
            ++j;

        prefix[i] = j;
    }

    auto iter = data.begin();

    ++iter;

    int j = 0;

    for (int i = 0; i < textLength; ++i, ++iter) {

        while (j > 0 && text[i] != pattern[j])
            j = prefix[j - 1];


        if (text[i] == pattern[j])
            ++j;

        match[i] = j;

        if (j == patternLength) {
            for (int t = 0; t < patternLength; ++t)
                data.erase(std::prev(iter));

            if (iter == data.begin()) {
                j = 0;
            } else {
                j = match[*std::prev(iter)];
            }
        }
    }

    for (auto const &iter: data)
        std::cout << text[iter];

    std::cout << std::flush;

    return 0;
}
