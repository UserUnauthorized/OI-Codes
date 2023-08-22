//Codeforces - 1798E
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MIN = INT_MIN >> 2;

int main() {
    valueType T;

    std::cin >> T;

    for (valueType testcase = 0; testcase < T; ++testcase) {
        valueType N;

        std::cin >> N;

        ValueVector source(N + 2), next(N + 2, N + 2), F(N + 2, MIN), G(N + 2, MIN), maxF(N + 2, MIN);

        for (valueType i = 1; i <= N; ++i) {
            std::cin >> source[i];
            next[i] = i + source[i] + 1;
        }

        maxF[N + 1] = F[N + 1] = G[N + 1] = 0;

        for (valueType i = N; i > 1; --i) {
            if (next[i] <= N + 1)
                F[i] = F[next[i]] + 1;

            G[i] = maxF[i + 1] + 1;

            if (next[i] <= N + 1)
                G[i] = std::max({G[i], G[next[i]] + 1});

            maxF[i] = std::max(maxF[i + 1], F[i]);
        }

        for (valueType i = 1; i < N; ++i) {
            if (source[i] == F[i + 1]) {
                std::cout << 0 << ' ';
            } else if (F[i + 1] > 0 || G[i + 1] >= source[i]) {
                std::cout << 1 << ' ';
            } else {
                std::cout << 2 << ' ';
            }
        }

        std::cout << '\n';
    }

    std::cout << std::flush;

    return 0;
}