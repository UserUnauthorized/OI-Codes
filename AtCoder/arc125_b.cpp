#include <bits/stdc++.h>

typedef long long valueType;

constexpr valueType MOD = 998244353;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N;

    std::cin >> N;

    valueType ans = 0;

    for (valueType i = 1; i * i <= N; ++i) {
        ans += (std::min((N - i * i) / (2 * i), N - i) + 1) % MOD;

        ans %= MOD;
    }

    std::cout << ans << std::endl;

    return 0;
}