//Luogu - UVA10576
#include <bits/stdc++.h>

typedef long long valueType;

int main() {
    valueType S, D;

    while (std::cin >> S >> D) {
        valueType now = 0;

        valueType SCount = 0, DCount = 0;

        for (int i = 0; i < 5; ++i) {
            if (now + S >= 0) {
                now -= D;
                ++DCount;
            } else {
                now += S;
                ++SCount;
            }
        }

        valueType result = 2 * (SCount * S - DCount * D);

        if (SCount >= 2)
            result += 2 * S;
        else
            result += SCount * S - (2 - SCount) * D;

        if (result < 0)
            std::cout << "Deficit\n";
        else
            std::cout << result << '\n';
    }

    return 0;
}
