//HZ - 32.4
//Luogu - P2627
#include <bits/stdc++.h>

using namespace std;
constexpr long long maxn = 100005;
long long n, K;
long long source[maxn], sum[maxn], dp[maxn];

void init();

int main() {
    init();
    deque<int> que;
    for (int i = 1; i <= n; ++i) {
        while (!que.empty() && dp[que.back() - 1] - sum[que.back()] < dp[i - 2] - sum[i - 1])
            que.pop_back();
        que.push_back(i - 1);
        while (!que.empty() && que.front() < i - K)
            que.pop_front();
        dp[i] = dp[que.front() - 1] - sum[que.front()] + sum[i];
    }
    printf("%lld", dp[n]);
    return 0;
}

void init() {
    memset(source, 0, sizeof(source));
    memset(sum, 0, sizeof(sum));
    memset(dp, 0, sizeof(dp));

    scanf("%lld%lld", &n, &K);

    for (int i = 1; i <= n; ++i)
        scanf("%lld", source + i);

    partial_sum(source + 1, source + n + 1, sum + 1);
}