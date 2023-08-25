//AT_arc148_d
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N, M;
    std::cin >> N >> M;
    ValueVector source(2 * N);

    for (auto &iter: source) {
        std::cin >> iter;

        iter %= M;
    }

    std::sort(source.begin(), source.end());

    for (valueType i = 0; i < N; ++i) {
        if (source[i << 1] != source[i << 1 | 1]) {
            std::cout << "Alice" << std::endl;

            return 0;
        }
    }

    std::cout << "Bob" << std::endl;

    return 0;
}