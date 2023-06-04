//HZ - 37.9
//Luogu - P3435
#include<bits/stdc++.h>

typedef long long valueType;

constexpr valueType maxN = 1e6 + 5;

std::array<valueType, maxN> next;

valueType ans = 0, K;

int main() {
    std::string text;

    std::cin >> K >> text;

    valueType const length = text.length();

    int j = 0;

    for (int i = 1; i < length; ++i) {
        while (j > 0 && text[i] != text[j])
            j = next[j - 1];

        if (text[i] == text[j])
            ++j;


        next[i] = j;
    }

    for (int i = 1; i < length; ++i) {
        j = next[i];

        while (next[j - 1] != 0)
            j = next[j - 1];

        if (j != 0)
            ans += i + 1 - j;

        next[i] = j;
    }

    std::cout << ans << std::flush;

    return 0;
}
