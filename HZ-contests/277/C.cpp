//HZ - 277.3
#include<bits/stdc++.h>

using namespace std;
const int maxn = 50004, maxm = 54;

inline long long read();

inline void init();

inline long long check(int, int);

long long T, n, m, sum, ans, t, dp[maxn][maxm], score[maxn];

int main() {
    T = read();
    while (T--) {
        init();

        t = score[1] + score[2] * 2 + score[3] * 4;
        for (int i = 4; i <= n; i++)
            t += score[i] * 8;
        if (m == 0 || n >= 4)
            ans = max(ans, t - check(4, (int) m));


        t = score[2] + score[3] * 2 + score[4] * 4;
        for (int i = 5; i <= n; i++)
            t += score[i] * 8;
        ans = max(ans, t - check(5, (int) m - 1));


        t = score[1] + score[3] + score[4] * 2 + score[5] * 4;
        for (int i = 6; i <= n; i++)
            t += score[i] * 8;
        if (n >= 2)
            ans = max(ans, t - check(6, (int) m - 1));


        t = score[1] + score[2] * 2 + score[4] + score[5] * 2 + score[6] * 4;
        for (int i = 7; i <= n; i++)
            t += score[i] * 8;
        if (n >= 3)
            ans = max(ans, t - check(7, (int) m - 1));

        printf("%lld\n", ans);
    }
    return 0;
}

inline long long read() {
    int ch(getchar());
    long long result(0);
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        result = (result << 3) + (result << 1) + (ch ^ 48);
        ch = getchar();
    }
    return result;
}

inline void write(int *result) {
    int ch(getchar());
    bool positive(true);
    while ((ch < '0' || ch > '9') && ch != '-')
        ch = getchar();
    if (ch == '-') {
        positive = false;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        *result = (*result << 3) + (*result << 1) + (ch ^ 48);
        ch = getchar();
    }
    if (!positive)
        *result = -*result;
}

inline void init() {
    memset(score, 0, sizeof(score));

    n = read();
    m = read();
    sum = 0;
    ans = LONG_LONG_MIN;

    for (int i = 0; i <= n; ++i) {
        for (int j = 1; j <= m; ++j)
            dp[i][j] = LONG_LONG_MAX;
        dp[i][0] = 0;
    }

    for (int i = 1; i <= n; ++i) {
        int k = read();
        for (int j = 0; j < k; ++j) {
            score[i] += read();
        }
        sum += score[i] * 8;
    }
}

inline long long check(int start, int M) {
    if (M < 0)
        return LONG_LONG_MAX / 2;

    for (int i = 0; i <= n; ++i) {
        for (int j = 1; j <= m; ++j)
            dp[i][j] = LONG_LONG_MAX / 2;
        dp[i][0] = 0;
    }

    for (int i = start; i <= n; ++i)
        for (int j = 1; j <= M; ++j)
            dp[i][j] = min(dp[i - 1][j],
                           dp[i - 4][j - 1] + score[i] * 8 + score[i + 1] * 7 + score[i + 2] * 6 + score[i + 3] * 4);

    return dp[n][M];
}
