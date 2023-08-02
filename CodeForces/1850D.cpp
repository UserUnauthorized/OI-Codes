//CodeForces - 1850D
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

int main() {
    valueType T;

    std::cin >> T;

    for (valueType testcase = 0; testcase < T; ++testcase) {
        valueType N, K;

        std::cin >> N >> K;

        ValueVector source(N);

        for (auto &iter: source)
            std::cin >> iter;

        source.push_back(LONG_LONG_MAX >> 5);

        std::sort(source.begin(), source.end());

        valueType last = -1, max = 0;

        for (valueType i = 0; i < N; ++i) {
            if (source[i + 1] - source[i] > K) {
                max = std::max(max, i - last);
                last = i;
            }
        }

        std::cout << (N - max) << '\n';
    }

    std::cout << std::flush;

    return 0;
}