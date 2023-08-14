// AT_arc131_c
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;

int main() {
    valueType N;

    std::cin >> N;

    ValueVector source(N);

    for (auto &iter: source)
        std::cin >> iter;

    if (std::find(source.begin(), source.end(), std::accumulate(source.begin(), source.end(), 0, std::bit_xor<>())) !=
        source.end()) {
        std::cout << "Win" << std::endl;

        return 0;
    }

    std::cout << ((N & 1) ? "Win" : "Lose") << std::endl;

    return 0;
}
