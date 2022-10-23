//HZ - 20.8
//Luogu - P4147
#include<bits/stdc++.h>

using namespace std;

int dp[1002][1002], n, m, s[1002][1002], us[1002][1002], ds[1002][1002];

int ans = 0;

bool g[1002][1002];

deque<int> que;

void init();
void DP();
void empty();

int main() {
    init();
    DP();
    for (int j = 1; j <= m; ++j) {
        for (int i = 1; i <= n + 1; ++i) {
            while (!que.empty() && dp[que.back()][j] > dp[i][j]) {
                ds[que.back()][j] = i - que.back();
                //if(i < n+1) ++ds[que.back()][j];
                que.pop_back();
            }
            que.push_back(i);
        }

        empty();

        for (int i = n; i >= 0; --i) {
            while (!que.empty() && dp[que.back()][j] > dp[i][j]) {
                us[que.back()][j] = que.back() - i;
                //if(i > 0) ++us[que.back()][j];
                que.pop_back();
            }
            que.push_back(i);
        }

        empty();
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            ans = max(ans, dp[i][j] * (us[i][j] + ds[i][j] - 1));
        }
    }

    ans *= 3;

    printf("%d", ans);
}

void init() {
    memset(dp, 0, sizeof(dp));
    memset(g, 0, sizeof(g));
    memset(s, 0, sizeof(s));
    memset(us, 0, sizeof(us));
    memset(ds, 0, sizeof(ds));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            char ch(getchar());
            while (ch != 'R' && ch != 'F') ch = getchar();
            g[i][j] = (ch == 'F');
        }
    }
    for (int i = 1; i <= n; ++i) dp[i][m + 1] = dp[i][0] = -1;
    for (int i = 1; i <= m + 1; ++i) dp[n + 1][i] = dp[0][i] = -1;
}

void DP() {
    for (int i = 1; i <= n; ++i) {
        if (g[i][m]) {
            dp[i][m] = 1;
        }
    }
    for (int j = m - 1; j >= 1; --j) {
        for (int i = 1; i <= n; ++i) {
            if (g[i][j]) {
                dp[i][j] = dp[i][j + 1] + 1;
            } else {
                dp[i][j] = 0;
            }
        }
    }
}

void empty() {
    deque<int> empty;
    que.swap(empty);
}
