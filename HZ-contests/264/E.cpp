//HZ - 264.5
#include <bits/stdc++.h>

using namespace std;

inline int read();

inline long long fastPower(long long, long long);

inline bool cmp(const int &, const int &);

void init();

constexpr int maxn = 100005, P = 1e9 + 7;
int n, m, x, y;
long long source[maxn];
long long ans;

int main() {
    freopen("xin.in", "r", stdin);
    freopen("xin.out", "w", stdout);
    init();
    sort(source + 1, source + n + 1, cmp);
    long long A = fastPower(3, m) % P;
    long long B = fastPower(2, m) % P;

    for (int i = 1; i <= x && i <= n; ++i) {
        ans += source[i] * A % P;
        ans %= P;
    }
    for (int i = x + 1; i <= x + y && i <= n; ++i) {
        ans += source[i] * B % P;
        ans %= P;
    }
    for (int i = min(x + y + 1, n + 1); i <= n && m < 2; ++i) {
        ans += source[i];
        ans %= P;
    }

    printf("%lld", ans % P);
    fclose(stdin);
    fclose(stdout);
    return 0;
}

void init() {
    memset(source, 0, sizeof(source));
    n = read();
    m = read();
    x = read();
    y = read();

    for (int i = 1; i <= n; ++i)
        source[i] = read();
}

inline bool cmp(const int &a, const int &b) {
    return a > b;
}

inline long long fastPower(long long a, long long b) {
    long long result(1);
    while (b > 0) {
        if (b & 1) result *= a;
        result %= P;
        a *= a;
        a %= P;
        b >>= 1;
    }
    return result;
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