#include <bits/stdc++.h>

typedef long long valueType;

valueType pow(valueType a, valueType b) {
    valueType result = 1;

    while (b > 0) {
        if (b & 1)
            result = result * a;

        a = a * a;
        b = b >> 1;
    }

    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N, P;

    std::cin >> N >> P;

    if (N == 1) {
        std::cout << P << std::endl;

        return 0;
    }

    valueType const M = std::floor(std::pow((long double) P, 1.0 / (long double) N));

    for (valueType i = M; i >= 1; --i) {
        if (P % pow(i, N) == 0) {
            std::cout << i << std::endl;

            return 0;
        }
    }

    return 0;
}