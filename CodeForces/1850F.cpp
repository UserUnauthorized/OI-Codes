//CodeForces - 1850F
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;

int main() {
    valueType T;

    std::cin >> T;

    for (valueType testcase = 0; testcase < T; ++testcase) {
        valueType N;

        std::cin >> N;

        ValueVector source(N + 1, 0);

        for (valueType i = 0; i < N; ++i) {
            valueType a;

            std::cin >> a;

            if (a <= N)
                ++source[a];
        }

        ValueVector count(N + 1, 0);

        valueType ans = -1;
        for (valueType i = 1; i <= N; ++i) {
            for (valueType j = i; j <= N; j += i)
                count[j] += source[i];

            ans = std::max(ans, count[i]);
        }

        std::cout << ans << '\n';
    }

    std::cout << std::flush;

    return 0;
}