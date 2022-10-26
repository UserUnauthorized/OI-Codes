//HZ - 264.5
#include <bits/stdc++.h>

using namespace std;

inline int read();

inline long long fastPower(long long, long long);

inline bool cmp(const int &, const int &);

void init();

constexpr int maxn = 100005, maxm = 1e9 + 7,
        P = 1e9 + 7;
int n, m, x, y;
long long source[maxn];
long long ans, a(1), b(1);

int main() {
    //freopen("xin.in", "r", stdin);
    //freopen("xin.out", "w", stdout);
    init();
    for (int i = 1; i <= m; ++i) {
        a *= 3;
        b *= 2;
        a %= P;
        b %= P;
        for (int j = 1; j <= x; ++j) {
            ans += source[j] * a;
            ans %= P;
        }
        for (int j = x + 1; j <= x + y && j <= n; ++j) {
            ans += source[j] * b;
            ans %= P;
        }
    }
    printf("%lld", ans);
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}

void init() {
    n = read();
    m = read();
    x = read();
    y = read();

    memset(source, 0, sizeof(source));
    for (int i = 1; i <= n; ++i)
        source[i] = read();
    sort(source + 1, source + n + 1, cmp);
}

inline bool cmp(const int &a, const int &b) {
    return a > b;
}

inline long long fastPower(long long a, long long b) {
    long long res(1);
    while (b > 0) {
        if (b & 1) res *= a;
        res %= P;
        a *= a;
        a %= P;
        b >>= 1;
    }
    return res;
}

inline int read() {
    int result(0), ch(getchar());
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        result = (result << 3) + (result << 1) + (ch ^ 48);
        ch = getchar();
    }
    return result;
}