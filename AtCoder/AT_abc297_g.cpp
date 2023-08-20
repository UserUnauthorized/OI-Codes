//AtCode - ABC297 - G
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

int main() {
    valueType N, L, R;

    std::cin >> N >> L >> R;

    valueType SG = 0;

    for (valueType i = 0; i < N; ++i) {
        valueType A;

        std::cin >> A;

        SG ^= (A % (L + R)) / L;
    }

    if (SG > 0)
        std::cout << "First" << std::endl;
    else
        std::cout << "Second" << std::endl;

    return 0;
}