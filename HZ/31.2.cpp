//HZ - 31.2
//Luogu - P1896
#include<bits/stdc++.h>

using namespace std;

constexpr int maxn = 10, maxs = 1 << 9;

unsigned long long n, k, cnt(0), ans(0);
unsigned int dp[maxn][maxs][maxn * maxn];
unsigned int bit[maxs], sum[maxs];

inline void init();

inline bool compatible(int x, int y);

void dfs(int x, int num, int current);

int main() {
    init();

    for (int j = 1; j <= cnt; ++j)dp[1][j][sum[j]] = 1;

    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= cnt; ++j)
            for (int x = 1; x <= cnt; ++x)
                if (compatible(j, x))
                    for (int t = sum[x]; t <= k; ++t)
                        dp[i][x][t] += dp[i - 1][j][t - sum[x]];

    for (int j = 1; j <= cnt; ++j)
        ans += dp[n][j][k];

    cout << ans;
    return 0;
}

void init() {
    memset(dp, 0, sizeof(dp));
    memset(bit, 0, sizeof(bit));
    memset(sum, 0, sizeof(sum));

    cin >> n >> k;

    dfs(0, 0, 0);
}

void dfs(int x, int num, int current) {
    if (current >= n) {
        bit[++cnt] = x;
        sum[cnt] = num;
        return;
    }

    dfs(x + (1 << current), num + 1, current + 2);
    dfs(x, num, current + 1);
}

bool compatible(int x, int y) {
    return !(bit[x] & bit[y] || bit[x] & (bit[y] << 1) || (bit[x] << 1) & bit[y]);
}
