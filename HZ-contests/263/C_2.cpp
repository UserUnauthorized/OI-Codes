//HZ - 263.3
#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 1003;

int n;

double p[maxn], dp[maxn][maxn];

void init();

bool check(int);

int main() {
    init();
    for (int i = 0; i <= n; ++i)
        if (check(i)) {
            printf("%d", i);
            break;
        }
    return 0;
}

void init() {
    memset(p, 0, sizeof(p));
    memset(dp, 0, sizeof(dp));

    scanf("%d", &n);

    for (int i = 1; i <= n; ++i)
        scanf("%lf", p + i);
}

bool check(int x) {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1.0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j >= 0; --j) {
            if (j < (x + 1) >> 1) {
                dp[i][j + 1] += (p[i] * 0.5 * dp[i - 1][j]);
                dp[i][j] = (1 - p[i] * 0.5) * dp[i - 1][j];
            } else {
                dp[i][j + 1] += (p[i] * dp[i - 1][j]);
                dp[i][j] = (1 - p[i]) * dp[i - 1][j];
            }
        }
    }
    double result(0);
    for (int i = 0; i < x; ++i) {
        result += dp[n][i];
    }
    if (result >= 0.4)return true;
    else return false;
}