#include <bits/stdc++.h>

typedef long long valueType;

valueType popcount(valueType n) {
    return __builtin_popcountll(n);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType T;

    std::cin >> T;

    for (int testcase = 0; testcase < T; ++testcase) {
        valueType A, S;

        std::cin >> A >> S;

        if (A * 2 > S || ((S - 2 * A) & A)) {
            std::cout << "No\n";
        } else {
            std::cout << "Yes\n";
        }
    }

    std::cout << std::flush;

    return 0;
}