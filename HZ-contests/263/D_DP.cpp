//HZ - 263.4
#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 1000006;

int n, k, source[maxn], value[maxn];

long long sum, ans, dp[maxn];

void init();

int main() {
    init();
    for (int i = 1; i <= n; ++i) {
        sum += source[i];
        if (source[i] < k - 1)
            value[i] = 1;
        else
            value[i] = -k + 1;
        dp[i] = max((long long) value[i], dp[i - 1] + value[i]);
        ans = max(ans, dp[i]);
    }
    printf("%lld\n", sum + ans);
}

void init() {
    memset(source, 0, sizeof(source));
    memset(value, 0, sizeof(value));
    memset(dp, 0, sizeof(dp));

    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", source + i);
    }
}