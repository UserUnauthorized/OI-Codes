//Codeforces - CF803C
#include <bits/stdc++.h>

typedef long long valueType;

int main() {
    valueType N, K;

    std::cin >> N >> K;

    if (N / K < (K - 10) / 2) {
        std::cout << -1 << std::endl;

        return 0;
    }

    if (N < K * (K + 1) / 2) {
        std::cout << -1 << std::endl;

        return 0;
    }

    valueType const min = K * (K + 1) / 2;
    valueType const start = std::ceil(std::sqrt((long double) N) + 10);

    valueType result = 1;

    for(valueType i = start; i >= 1; --i) {
        if (N % i == 0) {
            if (N / i >= min)
                result = std::max(result, i);

            if (i >= min)
                result = std::max(result, N / i);
        }
    }

    valueType const remain = N / result - min;

    for(valueType i = 1; i < K; ++i)
        std::cout << i * result << ' ';

    std::cout << result * (K + remain) << std::endl;

    return 0;
}