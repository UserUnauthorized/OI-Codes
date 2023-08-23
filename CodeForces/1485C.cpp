//Codeforces - 1485C
#include <bits/stdc++.h>

typedef long long valueType;

int main() {
    valueType T;

    std::cin >> T;

    for (valueType testcase = 0; testcase < T; ++testcase) {
        valueType X, Y;

        std::cin >> X >> Y;

        valueType ans = 0;

        for (valueType i = 1; i * (i + 1) < X && i < Y; ++i) {
            ans += std::min(X / i - 1, Y) - i;
        }

        std::cout << ans << '\n';
    }

    std::cout << std::flush;

    return 0;
}