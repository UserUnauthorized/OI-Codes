//AT_past202005_j
#include<bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MAX = INT_MAX >> 1;

int main() {
    int N, M;

    std::cin >> N >> M;

    ValueVector data(N + 1, 0);

    data[0] = MAX;

    for (int i = 0; i < M; ++i) {
        int a;

        std::cin >> a;

        auto const iter = std::upper_bound(data.begin(), data.end(), a, std::greater<valueType>());

        if (iter == data.end()) {
            std::cout << "-1\n";
            continue;
        }

        *iter = a;

        std::cout << std::distance(data.begin(), iter) << '\n';
    }

    std::cout << std::flush;

    return 0;
}
