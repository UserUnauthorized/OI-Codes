//Luogu - P2197
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;

int main() {
    std::ios::sync_with_stdio(false);

    valueType T;

    std::cin >> T;

    for (valueType i = 0; i < T; ++i) {
        valueType N;

        std::cin >> N;

        ValueVector source(N);

        for (auto &iter: source)
            std::cin >> iter;

        std::cout << (std::accumulate(source.begin(), source.end(), 0, std::bit_xor<>()) == 0 ? "No" : "Yes") << '\n';
    }

    std::cout << std::flush;

    return 0;
}