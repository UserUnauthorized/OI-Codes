//Luogu - P1806
#include<bits/stdc++.h>

typedef long long valueType;

constexpr int maxN = 505;

std::array<std::array<valueType, maxN>, maxN> dp;

int main() {
    int N;

    std::cin >> N;

    dp[0][0] = 1;

    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < i; ++j) {
            valueType const difference = i - j;

            for (int k = 0; k < difference; ++k) {
                dp[i][difference] += dp[j][k];
            }
        }
    }

    valueType result = -1;

    for (int i = 1; i <= N; ++i)
        result += dp[N][i];

    std::cout << result << std::flush;

    return 0;
}
