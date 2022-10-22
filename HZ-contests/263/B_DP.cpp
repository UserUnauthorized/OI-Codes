//HZ - 263.2
#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 102;

constexpr int maxv = 1000006;

int n, sum = 0, value[maxn];

bool dp[maxv];

void init();

int main() {
    init();
    dp[0] = true;
    for (int i = 1; i <= n; ++i)
        sum += value[i];
    for (int i = 1; i <= n; ++i)
        for (int j = sum; j >= value[i]; --j)
            if (dp[j - value[i]])
                dp[j] = true;
    for (int i = sum / 2; i >= 0; --i)
        if (dp[i]) {
            printf("%d", sum - 2 * i);
            return 0;
        }
}

void init() {
    memset(value, 0, sizeof(value));
    memset(dp, 0, sizeof(dp));

    scanf("%d", &n);

    for (int i = 1; i <= n; ++i)
        scanf("%d", value + i);
}