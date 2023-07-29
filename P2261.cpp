//Luogu - P2261
#include <bits/stdc++.h>

typedef long long valueType;

int main() {
    valueType N, K;

    std::cin >> N >> K;

    valueType result = N * K;

    valueType l = 1, r;

    while (l <= std::min(K, N)) {
        r = K / (K / l);

        if (r > N)
            r = N;

        result -= (r * (r + 1) / 2 - l * (l - 1) / 2) * (K / l);

        l = r + 1;
    }

    std::cout << result << std::endl;
}