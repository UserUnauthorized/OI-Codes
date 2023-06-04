//HZ - 35.3
//Luogu - P1654
#include<bits/stdc++.h>

int main() {
    int N;

    std::cin >> N;

    std::vector<long double> P(N + 1), x1(N + 1, 0), x2(N + 1, 0), ans(N + 1, 0);

    for (int i = 1; i <= N; ++i)
        std::cin >> P[i];

    for (int i = 1; i <= N; ++i) {
        x1[i] = (x1[i - 1] + 1) * P[i];
        x2[i] = (x2[i - 1] + 2 * x1[i - 1] + 1) * P[i];
        ans[i] = ans[i - 1] + (3 * x2[i - 1] + 3 * x1[i - 1] + 1) * P[i];
    }

    std::cout << std::setprecision(1) << std::fixed << ans[N] << std::flush;

    return 0;
}
