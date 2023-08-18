//Codeforces - 1656D
#include <bits/stdc++.h>

typedef long long valueType;

valueType lowBit(valueType x) {
    return x & -x;
}

int main() {
    valueType T;

    std::cin >> T;

    for (valueType testcase = 0; testcase < T; ++testcase) {
        valueType N;

        std::cin >> N;

        valueType const bit = lowBit(N);

        valueType const x = N / bit, y = bit << 1;

        if (x == 1) {
            std::cout << -1 << '\n';
        } else {
            std::cout << std::min(x, y) << '\n';
        }
    }

    std::cout << std::flush;

    return 0;
}